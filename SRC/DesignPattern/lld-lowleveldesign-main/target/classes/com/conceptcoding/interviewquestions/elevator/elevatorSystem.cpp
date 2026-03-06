#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <algorithm>
#include <chrono>
#include <atomic>

// =========================== ENUMS ===========================

enum class ElevatorDirection
{
    UP,
    DOWN,
    IDLE
};

enum class DoorState
{
    DOOR_OPEN,
    DOOR_CLOSED
};

// =========================== FORWARD DECLARATIONS ===========================

class ElevatorController;
class ExternalDispatcher;
class ElevatorScheduler;

// =========================== UTILITY FUNCTIONS ===========================

std::string directionToString(ElevatorDirection dir)
{
    switch (dir)
    {
    case ElevatorDirection::UP:
        return "UP";
    case ElevatorDirection::DOWN:
        return "DOWN";
    case ElevatorDirection::IDLE:
        return "IDLE";
    }
    return "UNKNOWN";
}

// =========================== DOOR CLASS ===========================

class Door
{
private:
    DoorState doorState;

public:
    Door() : doorState(DoorState::DOOR_CLOSED) {}

    void openDoor(int id)
    {
        doorState = DoorState::DOOR_OPEN;
        std::cout << "Opening the Elevator door of elevator:" << id << std::endl;
    }

    void closeDoor(int id)
    {
        doorState = DoorState::DOOR_CLOSED;
        std::cout << "Closing the Elevator door of elevator:" << id << std::endl;
    }

    DoorState getState() const { return doorState; }
};

// =========================== ELEVATOR CAR CLASS ===========================

class ElevatorCar
{
public:
    int id;
    std::atomic<int> currentFloor;
    std::atomic<int> nextFloorStoppage;
    std::atomic<ElevatorDirection> movingDirection;
    std::unique_ptr<Door> door;

    ElevatorCar(int id) : id(id), currentFloor(0), nextFloorStoppage(0),
                          movingDirection(ElevatorDirection::IDLE)
    {
        door = std::make_unique<Door>();
    }

    void showDisplay()
    {
        std::cout << "elevator:" << id << " Current floor: " << currentFloor.load()
                  << " going: " << directionToString(movingDirection.load()) << std::endl;
    }

    void moveElevator(int destinationFloor)
    {
        nextFloorStoppage.store(destinationFloor);

        if (currentFloor.load() == nextFloorStoppage.load())
        {
            door->openDoor(id);
            return;
        }

        int startFloor = currentFloor.load();
        door->closeDoor(id);

        if (nextFloorStoppage.load() >= currentFloor.load())
        {
            movingDirection.store(ElevatorDirection::UP);
            showDisplay();

            for (int i = startFloor + 1; i <= nextFloorStoppage.load(); i++)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // More visible delay
                setCurrentFloor(i);
                showDisplay();
            }
        }
        else
        {
            movingDirection.store(ElevatorDirection::DOWN);
            showDisplay();

            for (int i = startFloor - 1; i >= nextFloorStoppage.load(); i--)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // More visible delay
                setCurrentFloor(i);
                showDisplay();
            }
        }

        door->openDoor(id);
    }

    void setCurrentFloor(int floor)
    {
        currentFloor.store(floor);
    }
};

// =========================== STRATEGY PATTERN FOR ELEVATOR SELECTION ===========================

class ElevatorSelectionStrategy
{
public:
    virtual ~ElevatorSelectionStrategy() = default;
    virtual std::shared_ptr<ElevatorController> selectElevator(
        const std::vector<std::shared_ptr<ElevatorController>> &controllers,
        int requestFloor,
        ElevatorDirection direction) = 0;
};

class NearestElevatorStrategy : public ElevatorSelectionStrategy
{
public:
    std::shared_ptr<ElevatorController> selectElevator(
        const std::vector<std::shared_ptr<ElevatorController>> &controllers,
        int requestFloor,
        ElevatorDirection direction) override;
};

class LeastBusyStrategy : public ElevatorSelectionStrategy
{
public:
    std::shared_ptr<ElevatorController> selectElevator(
        const std::vector<std::shared_ptr<ElevatorController>> &controllers,
        int requestFloor,
        ElevatorDirection direction) override;
};

// =========================== ELEVATOR CONTROLLER CLASS ===========================

class ElevatorController
{
private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> upMinPQ; // Min heap for UP
    std::priority_queue<int> downMaxPQ;                                    // Max heap for DOWN

    std::mutex queueMutex;
    std::condition_variable cv;
    std::atomic<bool> running{true};

public:
    std::shared_ptr<ElevatorCar> elevatorCar;

    ElevatorController(std::shared_ptr<ElevatorCar> car) : elevatorCar(car) {}

    ~ElevatorController()
    {
        running.store(false);
        cv.notify_all();
    }

    void submitRequest(int destinationFloor)
    {
        enqueueRequest(destinationFloor);
    }

    void stop()
    {
        running.store(false);
        cv.notify_all();
    }

    int getQueueSize() const
    {
        std::lock_guard<std::mutex> lock(const_cast<std::mutex &>(queueMutex));
        return upMinPQ.size() + downMaxPQ.size();
    }

private:
    void enqueueRequest(int destinationFloor)
    {
        std::cout << "Request details-> destinationFloor: " << destinationFloor
                  << " accepted by elevator:" << elevatorCar->id << std::endl;

        {
            std::lock_guard<std::mutex> lock(queueMutex);

            if (destinationFloor == elevatorCar->nextFloorStoppage.load())
            {
                return;
            }

            if (destinationFloor >= elevatorCar->nextFloorStoppage.load())
            {
                // Check if already exists
                std::priority_queue<int, std::vector<int>, std::greater<int>> tempUp = upMinPQ;
                bool found = false;
                while (!tempUp.empty() && !found)
                {
                    if (tempUp.top() == destinationFloor)
                    {
                        found = true;
                    }
                    tempUp.pop();
                }
                if (!found)
                {
                    upMinPQ.push(destinationFloor);
                }
            }
            else
            {
                // Check if already exists
                std::priority_queue<int> tempDown = downMaxPQ;
                bool found = false;
                while (!tempDown.empty() && !found)
                {
                    if (tempDown.top() == destinationFloor)
                    {
                        found = true;
                    }
                    tempDown.pop();
                }
                if (!found)
                {
                    downMaxPQ.push(destinationFloor);
                }
            }
        }

        cv.notify_one();
    }

public:
    void run()
    {
        controlElevator();
    }

private:
    void controlElevator()
    {
        while (running.load())
        {
            std::unique_lock<std::mutex> lock(queueMutex);

            // Wait for requests
            cv.wait(lock, [this]
                    { return !running.load() || !upMinPQ.empty() || !downMaxPQ.empty(); });

            if (!running.load())
            {
                break;
            }

            if (upMinPQ.empty() && downMaxPQ.empty())
            {
                std::cout << "elevator:" << elevatorCar->id << " is IDLE" << std::endl;
                elevatorCar->movingDirection.store(ElevatorDirection::IDLE);
                continue;
            }

            // Process UP requests
            while (!upMinPQ.empty() && running.load())
            {
                int floor = upMinPQ.top();
                upMinPQ.pop();
                lock.unlock();

                std::cout << "Serving floor: " << floor << " by elevator:" << elevatorCar->id
                          << " currentFloor: " << elevatorCar->currentFloor.load() << std::endl;
                elevatorCar->moveElevator(floor);

                lock.lock();
            }

            // Process DOWN requests
            while (!downMaxPQ.empty() && running.load())
            {
                int floor = downMaxPQ.top();
                downMaxPQ.pop();
                lock.unlock();

                std::cout << "Serving floor: " << floor << " by elevator:" << elevatorCar->id
                          << " currentFloor: " << elevatorCar->currentFloor.load() << std::endl;
                elevatorCar->moveElevator(floor);

                lock.lock();
            }
        }
    }
};

// =========================== STRATEGY IMPLEMENTATIONS ===========================

std::shared_ptr<ElevatorController> NearestElevatorStrategy::selectElevator(
    const std::vector<std::shared_ptr<ElevatorController>> &controllers,
    int requestFloor,
    ElevatorDirection direction)
{

    std::shared_ptr<ElevatorController> best = nullptr;
    int minDistance = INT_MAX;

    // Pick the one which is going in same direction and minimum distance from the destination
    for (auto &controller : controllers)
    {
        int nextFloorStoppage = controller->elevatorCar->nextFloorStoppage.load();
        ElevatorDirection currentDirection = controller->elevatorCar->movingDirection.load();

        // Good candidate if moving same direction & not passed requested floor
        bool isSameDirectionCandidate =
            currentDirection == direction &&
            ((direction == ElevatorDirection::UP && nextFloorStoppage <= requestFloor) ||
             (direction == ElevatorDirection::DOWN && nextFloorStoppage >= requestFloor));

        int dist = abs(nextFloorStoppage - requestFloor);

        if (isSameDirectionCandidate && dist < minDistance)
        {
            minDistance = dist;
            best = controller;
        }
    }

    // fallback: if not able to choose, pick the idle one
    if (best == nullptr)
    {
        for (auto &controller : controllers)
        {
            if (controller->elevatorCar->movingDirection.load() == ElevatorDirection::IDLE)
            {
                best = controller;
                break;
            }
        }

        // reached here means, no elevator is going in same direction and no elevator is IDLE too, then pick any
        if (best == nullptr && !controllers.empty())
        {
            best = controllers[0];
        }
    }

    return best;
}

std::shared_ptr<ElevatorController> LeastBusyStrategy::selectElevator(
    const std::vector<std::shared_ptr<ElevatorController>> &controllers,
    int requestFloor,
    ElevatorDirection direction)
{

    std::shared_ptr<ElevatorController> best = nullptr;
    int minLoad = INT_MAX;

    for (auto &controller : controllers)
    {
        int load = controller->getQueueSize();

        if (load < minLoad)
        {
            minLoad = load;
            best = controller;
        }
    }

    return best;
}

// =========================== DISPATCHER CLASSES ===========================

class InternalDispatcher
{
private:
    static std::unique_ptr<InternalDispatcher> instance;
    static std::once_flag initFlag;

    InternalDispatcher() = default;

public:
    static InternalDispatcher &getInstance()
    {
        std::call_once(initFlag, []()
                       { instance = std::unique_ptr<InternalDispatcher>(new InternalDispatcher()); });
        return *instance;
    }

    void submitInternalRequest(int destinationFloor, std::shared_ptr<ElevatorController> controller)
    {
        controller->submitRequest(destinationFloor);
    }
};

// Static member definitions
std::unique_ptr<InternalDispatcher> InternalDispatcher::instance = nullptr;
std::once_flag InternalDispatcher::initFlag;

class ExternalDispatcher
{
private:
    std::shared_ptr<ElevatorScheduler> scheduler;

public:
    ExternalDispatcher(std::shared_ptr<ElevatorScheduler> scheduler) : scheduler(scheduler) {}

    void submitExternalRequest(int floor, ElevatorDirection direction);
};

// =========================== SCHEDULER CLASS ===========================

class ElevatorScheduler
{
private:
    std::vector<std::shared_ptr<ElevatorController>> controllers;
    std::unique_ptr<ElevatorSelectionStrategy> strategy;
    mutable std::mutex schedulerMutex; // Protects strategy and ensures atomic elevator assignment

public:
    ElevatorScheduler(std::vector<std::shared_ptr<ElevatorController>> controllers,
                      std::unique_ptr<ElevatorSelectionStrategy> strategy)
        : controllers(std::move(controllers)), strategy(std::move(strategy)) {}

    void setStrategy(std::unique_ptr<ElevatorSelectionStrategy> newStrategy)
    {
        std::lock_guard<std::mutex> lock(schedulerMutex);
        strategy = std::move(newStrategy);
        std::cout << "Strategy changed successfully (thread-safe)" << std::endl;
    }

    std::shared_ptr<ElevatorController> assignElevator(int floor, ElevatorDirection direction)
    {
        std::lock_guard<std::mutex> lock(schedulerMutex);
        // Critical section: ensures atomic read of elevator states and assignment
        return strategy->selectElevator(controllers, floor, direction);
    }
};

// External dispatcher implementation
void ExternalDispatcher::submitExternalRequest(int floor, ElevatorDirection direction)
{
    auto controller = scheduler->assignElevator(floor, direction);
    if (controller)
    {
        controller->submitRequest(floor);
    }
}

// =========================== BUTTON CLASSES ===========================

class ExternalButton
{
private:
    std::shared_ptr<ExternalDispatcher> dispatcher;

public:
    ExternalButton(std::shared_ptr<ExternalDispatcher> dispatcher) : dispatcher(dispatcher) {}

    void pressButton(int floor, ElevatorDirection direction)
    {
        dispatcher->submitExternalRequest(floor, direction);
    }
};

class InternalButton
{
private:
    std::shared_ptr<ElevatorController> controller;

public:
    InternalButton(std::shared_ptr<ElevatorController> controller) : controller(controller) {}

    void pressButton(int destinationFloor)
    {
        InternalDispatcher::getInstance().submitInternalRequest(destinationFloor, controller);
    }
};

// =========================== FLOOR CLASS ===========================

class Floor
{
private:
    int floorNumber;
    std::unique_ptr<ExternalButton> upButton;
    std::unique_ptr<ExternalButton> downButton;

public:
    Floor(int floorNumber, std::shared_ptr<ExternalDispatcher> dispatcher) : floorNumber(floorNumber)
    {
        upButton = std::make_unique<ExternalButton>(dispatcher);
        downButton = std::make_unique<ExternalButton>(dispatcher);
    }

    void pressUpButton()
    {
        upButton->pressButton(floorNumber, ElevatorDirection::UP);
    }

    void pressDownButton()
    {
        downButton->pressButton(floorNumber, ElevatorDirection::DOWN);
    }

    int getFloorNumber() const { return floorNumber; }
};

// =========================== BUILDING CLASS ===========================

class Building
{
private:
    std::vector<std::unique_ptr<Floor>> floors;

public:
    Building(int totalFloors, std::shared_ptr<ExternalDispatcher> dispatcher)
    {
        for (int i = 1; i <= totalFloors; i++)
        {
            floors.push_back(std::make_unique<Floor>(i, dispatcher));
        }
    }

    Floor *getFloor(int floorNumber)
    {
        if (floorNumber >= 1 && floorNumber <= static_cast<int>(floors.size()))
        {
            return floors[floorNumber - 1].get();
        }
        return nullptr;
    }

    int getTotalFloors() const { return floors.size(); }
};

// =========================== MAIN DEMO ===========================

class ElevatorSystem
{
private:
    std::vector<std::shared_ptr<ElevatorController>> controllers;
    std::vector<std::thread> threads;
    std::unique_ptr<Building> building;

public:
    void initialize()
    {
        // 1. Create elevator cars and their controllers
        auto car1 = std::make_shared<ElevatorCar>(1);
        auto controller1 = std::make_shared<ElevatorController>(car1);

        auto car2 = std::make_shared<ElevatorCar>(2);
        auto controller2 = std::make_shared<ElevatorController>(car2);

        controllers.push_back(controller1);
        controllers.push_back(controller2);

        // 2. Create internal buttons for each elevator
        auto internalButton1 = std::make_unique<InternalButton>(controller1);
        auto internalButton2 = std::make_unique<InternalButton>(controller2);

        // 3. Create Scheduler with Nearest Strategy
        auto elevatorScheduler = std::make_shared<ElevatorScheduler>(
            controllers,
            std::make_unique<NearestElevatorStrategy>());

        // 4. Create External Dispatcher
        auto externalDispatcher = std::make_shared<ExternalDispatcher>(elevatorScheduler);

        // 5. Create a 5 floor building
        building = std::make_unique<Building>(5, externalDispatcher);

        // 6. Start both the elevator controller threads
        threads.emplace_back([controller1]()
                             { controller1->run(); });

        threads.emplace_back([controller2]()
                             { controller2->run(); });

        // Give threads time to start
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // 7. Submit the requests
        std::cout << "\n=== Starting Elevator System Demo ===" << std::endl;

        // External Call: Floor 3 UP
        std::cout << "\n1. External Call: Floor 3 UP" << std::endl;
        building->getFloor(3)->pressUpButton();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // External Call: Floor 5 DOWN
        std::cout << "\n2. External Call: Floor 5 DOWN" << std::endl;
        building->getFloor(5)->pressDownButton();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Internal Call: Elevator 1 (press 4)
        std::cout << "\n3. Internal Call: Elevator 1 to floor 4" << std::endl;
        internalButton1->pressButton(4);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Internal Call: Elevator 1 (press 5)
        std::cout << "\n4. Internal Call: Elevator 1 to floor 5" << std::endl;
        internalButton1->pressButton(5);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // External Call: Floor 1 DOWN
        std::cout << "\n5. External Call: Floor 1 DOWN" << std::endl;
        building->getFloor(1)->pressDownButton();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // External Call: Floor 2 UP
        std::cout << "\n6. External Call: Floor 2 UP" << std::endl;
        building->getFloor(2)->pressUpButton();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Internal Call: Elevator 1 (press 2)
        std::cout << "\n7. Internal Call: Elevator 1 to floor 2" << std::endl;
        internalButton1->pressButton(2);

        // Let the system process for a while
        std::cout << "\n=== Processing requests... ===" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // Test strategy change
        std::cout << "\n=== Changing strategy to LeastBusy ===" << std::endl;
        elevatorScheduler->setStrategy(std::make_unique<LeastBusyStrategy>());

        // More requests with new strategy
        std::cout << "\n8. External Call: Floor 4 UP (with LeastBusy strategy)" << std::endl;
        building->getFloor(4)->pressUpButton();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Let system process a bit more
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    void shutdown()
    {
        std::cout << "\n=== Shutting down elevator system ===" << std::endl;

        // Stop all controllers
        for (auto &controller : controllers)
        {
            controller->stop();
        }

        // Wait for all threads to finish
        for (auto &thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }

        std::cout << "Elevator system shutdown complete." << std::endl;
    }
};

// =========================== MAIN FUNCTION ===========================

int main()
{
    try
    {
        std::cout << "=== Elevator System Starting ===" << std::endl;

        ElevatorSystem system;
        system.initialize();

        // Let the demo run
        std::this_thread::sleep_for(std::chrono::seconds(5));

        system.shutdown();

        std::cout << "\n=== Demo completed successfully ===" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}