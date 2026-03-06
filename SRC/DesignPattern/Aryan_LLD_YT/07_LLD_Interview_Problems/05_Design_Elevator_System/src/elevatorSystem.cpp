#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <string>
#include <algorithm>
#include <functional>

// =========================== ENUMS ===========================

enum class Direction
{
    UP,   // The elevator is moving upward
    DOWN, // The elevator is moving downward
    IDLE  // The elevator is stationary, not moving
};

enum class ElevatorState
{
    IDLE,       // The elevator is not moving, waiting for requests
    MOVING,     // The elevator is in motion (either up or down)
    STOPPED,    // The elevator has temporarily stopped (e.g., at a floor)
    MAINTENANCE // The elevator is out of service and undergoing maintenance
};

// =========================== FORWARD DECLARATIONS ===========================

class Elevator;
class ElevatorRequest;

// =========================== BASIC CLASSES ===========================

class Floor
{
private:
    int floorNumber;

public:
    Floor(int floorNumber) : floorNumber(floorNumber) {}

    int getFloorNumber() const
    {
        return floorNumber;
    }
};

// =========================== OBSERVER PATTERN ===========================

class ElevatorObserver
{
public:
    virtual ~ElevatorObserver() = default;
    // Called when an elevator's state changes
    virtual void onElevatorStateChange(std::shared_ptr<Elevator> elevator, ElevatorState state) = 0;
    // Called when an elevator changes its current floor
    virtual void onElevatorFloorChange(std::shared_ptr<Elevator> elevator, int floor) = 0;
};

class ElevatorDisplay : public ElevatorObserver
{
public:
    void onElevatorStateChange(std::shared_ptr<Elevator> elevator, ElevatorState state) override;
    void onElevatorFloorChange(std::shared_ptr<Elevator> elevator, int floor) override;
};

// =========================== COMMAND PATTERN ===========================

class ElevatorCommand
{
public:
    virtual ~ElevatorCommand() = default;
    virtual void execute() = 0;
};

class ElevatorRequest : public ElevatorCommand
{
private:
    int elevatorId;             // ID of the elevator involved in the request
    int floor;                  // Floor where the request is made
    Direction requestDirection; // The direction of the elevator request
    bool isInternalRequest;     // Distinguishes internal vs external requests

public:
    ElevatorRequest(int elevatorId, int floor, bool isInternalRequest, Direction direction)
        : elevatorId(elevatorId), floor(floor), requestDirection(direction), isInternalRequest(isInternalRequest) {}

    void execute() override
    {
        // This would call controller methods, but simplified for this implementation
    }

    // Getters
    Direction getDirection() const { return requestDirection; }
    int getFloor() const { return floor; }
    bool checkIsInternalRequest() const { return isInternalRequest; }
    int getElevatorId() const { return elevatorId; }

    // Comparison operator for priority queues
    bool operator<(const ElevatorRequest &other) const
    {
        return floor < other.floor;
    }

    bool operator==(const ElevatorRequest &other) const
    {
        return floor == other.floor && elevatorId == other.elevatorId && isInternalRequest == other.isInternalRequest;
    }
};

// =========================== STRATEGY PATTERN ===========================

class SchedulingStrategy
{
public:
    virtual ~SchedulingStrategy() = default;
    virtual int getNextStop(std::shared_ptr<Elevator> elevator) = 0;
};

class FCFSSchedulingStrategy : public SchedulingStrategy
{
public:
    int getNextStop(std::shared_ptr<Elevator> elevator) override;
};

class ScanSchedulingStrategy : public SchedulingStrategy
{
public:
    int getNextStop(std::shared_ptr<Elevator> elevator) override;

private:
    template <typename T>
    int switchDirection(std::shared_ptr<Elevator> elevator, T &requestsQueue);
};

class LookSchedulingStrategy : public SchedulingStrategy
{
public:
    int getNextStop(std::shared_ptr<Elevator> elevator) override;
};

// =========================== ELEVATOR CLASS ===========================

class Elevator
{
private:
    int id;
    int currentFloor;
    Direction direction;
    ElevatorState state;
    std::vector<std::shared_ptr<ElevatorObserver>> observers;
    std::queue<std::shared_ptr<ElevatorRequest>> requests;

    // Notify all observers about a state change
    void notifyStateChange(ElevatorState state)
    {
        for (auto &observer : observers)
        {
            observer->onElevatorStateChange(shared_from_this(), state);
        }
    }

    // Notify all observers about a floor change
    void notifyFloorChange(int floor)
    {
        for (auto &observer : observers)
        {
            observer->onElevatorFloorChange(shared_from_this(), floor);
        }
    }

    // Handle the elevator's arrival at a destination floor
    void completeArrival()
    {
        setState(ElevatorState::STOPPED);

        // Remove the current floor from the requests queue
        std::queue<std::shared_ptr<ElevatorRequest>> tempQueue;
        while (!requests.empty())
        {
            auto request = requests.front();
            requests.pop();
            if (request->getFloor() != currentFloor)
            {
                tempQueue.push(request);
            }
        }
        requests = tempQueue;

        // If no more requests, set state to IDLE
        if (requests.empty())
        {
            direction = Direction::IDLE;
            setState(ElevatorState::IDLE);
        }
        else
        {
            setState(ElevatorState::MOVING);
        }
    }

public:
    Elevator(int id) : id(id), currentFloor(1), direction(Direction::IDLE), state(ElevatorState::IDLE) {}

    // Enable shared_from_this
    std::shared_ptr<Elevator> shared_from_this()
    {
        return std::shared_ptr<Elevator>(this, [](Elevator *) {});
    }

    // Add an observer to monitor elevator events
    void addObserver(std::shared_ptr<ElevatorObserver> observer)
    {
        observers.push_back(observer);
    }

    // Remove an observer
    void removeObserver(std::shared_ptr<ElevatorObserver> observer)
    {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    // Set a new state for the elevator and notify observers
    void setState(ElevatorState newState)
    {
        this->state = newState;
        notifyStateChange(newState);
    }

    // Set the direction of the elevator
    void setDirection(Direction newDirection)
    {
        this->direction = newDirection;
    }

    // Add a new floor request to the queue
    void addRequest(std::shared_ptr<ElevatorRequest> elevatorRequest)
    {
        // Avoid duplicate requests
        bool found = false;
        std::queue<std::shared_ptr<ElevatorRequest>> tempQueue = requests;
        while (!tempQueue.empty())
        {
            if (*tempQueue.front() == *elevatorRequest)
            {
                found = true;
                break;
            }
            tempQueue.pop();
        }

        if (!found)
        {
            requests.push(elevatorRequest);
        }

        int requestedFloor = elevatorRequest->getFloor();
        // If elevator is idle, determine direction and start moving
        if (state == ElevatorState::IDLE && !requests.empty())
        {
            if (requestedFloor > currentFloor)
            {
                direction = Direction::UP;
            }
            else if (requestedFloor < currentFloor)
            {
                direction = Direction::DOWN;
            }
            setState(ElevatorState::MOVING);
        }
    }

    // Move the elevator to the next stop as decided by the scheduling strategy
    void moveToNextStop(int nextStop)
    {
        if (state != ElevatorState::MOVING)
            return;

        while (currentFloor != nextStop)
        {
            if (direction == Direction::UP)
            {
                currentFloor++;
            }
            else
            {
                currentFloor--;
            }

            notifyFloorChange(currentFloor);

            if (currentFloor == nextStop)
            {
                completeArrival();
                return;
            }
        }
    }

    // Getters
    int getId() const { return id; }
    int getCurrentFloor() const { return currentFloor; }
    Direction getDirection() const { return direction; }
    ElevatorState getState() const { return state; }

    std::queue<std::shared_ptr<ElevatorRequest>> getRequestsQueue() const
    {
        return requests;
    }

    std::vector<std::shared_ptr<ElevatorRequest>> getDestinationFloors() const
    {
        std::vector<std::shared_ptr<ElevatorRequest>> destinations;
        std::queue<std::shared_ptr<ElevatorRequest>> tempQueue = requests;
        while (!tempQueue.empty())
        {
            destinations.push_back(tempQueue.front());
            tempQueue.pop();
        }
        return destinations;
    }
};

// =========================== STRATEGY IMPLEMENTATIONS ===========================

int FCFSSchedulingStrategy::getNextStop(std::shared_ptr<Elevator> elevator)
{
    Direction elevatorDirection = elevator->getDirection();
    int currentFloor = elevator->getCurrentFloor();

    auto requestQueue = elevator->getRequestsQueue();

    if (requestQueue.empty())
        return currentFloor;

    int nextRequestedFloor = requestQueue.front()->getFloor();

    if (nextRequestedFloor == currentFloor)
        return currentFloor;

    if (elevatorDirection == Direction::IDLE)
    {
        elevator->setDirection(nextRequestedFloor > currentFloor ? Direction::UP : Direction::DOWN);
    }
    else if (elevatorDirection == Direction::UP && nextRequestedFloor < currentFloor)
    {
        elevator->setDirection(Direction::DOWN);
    }
    else if (nextRequestedFloor > currentFloor)
    {
        elevator->setDirection(Direction::UP);
    }

    return nextRequestedFloor;
}

int ScanSchedulingStrategy::getNextStop(std::shared_ptr<Elevator> elevator)
{
    Direction elevatorDirection = elevator->getDirection();
    int currentFloor = elevator->getCurrentFloor();
    auto requests = elevator->getRequestsQueue();

    if (requests.empty())
        return currentFloor;

    std::priority_queue<std::shared_ptr<ElevatorRequest>> upQueue;
    std::priority_queue<std::shared_ptr<ElevatorRequest>, std::vector<std::shared_ptr<ElevatorRequest>>,
                        std::function<bool(const std::shared_ptr<ElevatorRequest> &, const std::shared_ptr<ElevatorRequest> &)>>
        downQueue([](const std::shared_ptr<ElevatorRequest> &a, const std::shared_ptr<ElevatorRequest> &b)
                  {
                      return a->getFloor() < b->getFloor(); // Max heap for downward
                  });

    while (!requests.empty())
    {
        auto elevatorRequest = requests.front();
        requests.pop();

        int floor = elevatorRequest->getFloor();
        if (floor > currentFloor)
            upQueue.push(elevatorRequest);
        else
            downQueue.push(elevatorRequest);
    }

    if (elevatorDirection == Direction::IDLE)
    {
        int nearestUpwardRequest = upQueue.empty() ? -1 : upQueue.top()->getFloor();
        int nearestDownwardRequest = downQueue.empty() ? -1 : downQueue.top()->getFloor();

        if (nearestUpwardRequest == -1)
        {
            elevator->setDirection(Direction::DOWN);
            return downQueue.top()->getFloor();
        }
        else if (nearestDownwardRequest == -1)
        {
            elevator->setDirection(Direction::UP);
            return upQueue.top()->getFloor();
        }
        else
        {
            if (std::abs(nearestUpwardRequest - currentFloor) < std::abs(nearestDownwardRequest - currentFloor))
            {
                elevator->setDirection(Direction::UP);
                return upQueue.top()->getFloor();
            }
            else
            {
                elevator->setDirection(Direction::DOWN);
                return downQueue.top()->getFloor();
            }
        }
    }

    if (elevatorDirection == Direction::UP)
    {
        return !upQueue.empty() ? upQueue.top()->getFloor() : switchDirection(elevator, downQueue);
    }
    else
    {
        return !downQueue.empty() ? downQueue.top()->getFloor() : switchDirection(elevator, upQueue);
    }
}

template <typename T>
int ScanSchedulingStrategy::switchDirection(std::shared_ptr<Elevator> elevator, T &requestsQueue)
{
    elevator->setDirection(elevator->getDirection() == Direction::UP ? Direction::DOWN : Direction::UP);
    return requestsQueue.empty() ? elevator->getCurrentFloor() : requestsQueue.top()->getFloor();
}

int LookSchedulingStrategy::getNextStop(std::shared_ptr<Elevator> elevator)
{
    int currentFloor = elevator->getCurrentFloor();
    auto requests = elevator->getRequestsQueue();

    if (requests.empty())
    {
        return currentFloor;
    }

    auto primaryRequest = requests.front();
    int primaryFloor = primaryRequest->getFloor();

    Direction travelDirection;
    if (primaryFloor > currentFloor)
    {
        travelDirection = Direction::UP;
    }
    else if (primaryFloor < currentFloor)
    {
        travelDirection = Direction::DOWN;
    }
    else
    {
        return currentFloor;
    }

    int candidate = -1;
    std::queue<std::shared_ptr<ElevatorRequest>> tempQueue = requests;
    while (!tempQueue.empty())
    {
        auto req = tempQueue.front();
        tempQueue.pop();

        int reqFloor = req->getFloor();

        if (travelDirection == Direction::UP && reqFloor > currentFloor && reqFloor <= primaryFloor)
        {
            if (req->checkIsInternalRequest() ||
                (!req->checkIsInternalRequest() && req->getDirection() == Direction::UP))
            {
                if (candidate == -1 || reqFloor < candidate)
                {
                    candidate = reqFloor;
                }
            }
        }
        else if (travelDirection == Direction::DOWN && reqFloor < currentFloor && reqFloor >= primaryFloor)
        {
            if (req->checkIsInternalRequest() ||
                (!req->checkIsInternalRequest() && req->getDirection() == Direction::DOWN))
            {
                if (candidate == -1 || reqFloor > candidate)
                {
                    candidate = reqFloor;
                }
            }
        }
    }

    return (candidate != -1) ? candidate : primaryFloor;
}

// =========================== CONTROLLER AND BUILDING ===========================

class ElevatorController
{
private:
    std::vector<std::shared_ptr<Elevator>> elevators;
    std::vector<std::shared_ptr<Floor>> floors;
    std::shared_ptr<SchedulingStrategy> schedulingStrategy;
    int currentElevatorId;

    std::shared_ptr<Elevator> getElevatorById(int elevatorId)
    {
        for (auto &elevator : elevators)
        {
            if (elevator->getId() == elevatorId)
                return elevator;
        }
        return nullptr;
    }

public:
    ElevatorController() {}

    ElevatorController(int numberOfElevators, int numberOfFloors)
    {
        this->schedulingStrategy = std::make_shared<ScanSchedulingStrategy>();

        for (int i = 1; i <= numberOfElevators; i++)
        {
            elevators.push_back(std::make_shared<Elevator>(i));
        }

        for (int i = 1; i <= numberOfFloors; i++)
        {
            floors.push_back(std::make_shared<Floor>(i));
        }
    }

    void setSchedulingStrategy(std::shared_ptr<SchedulingStrategy> strategy)
    {
        this->schedulingStrategy = strategy;
    }

    void requestElevator(int elevatorId, int floorNumber, Direction direction)
    {
        std::cout << "External request: Floor " << floorNumber << ", Direction "
                  << (direction == Direction::UP ? "UP" : "DOWN") << std::endl;

        auto selectedElevator = getElevatorById(elevatorId);
        if (selectedElevator != nullptr)
        {
            selectedElevator->addRequest(
                std::make_shared<ElevatorRequest>(elevatorId, floorNumber, false, direction));
            std::cout << "Assigned elevator " << selectedElevator->getId()
                      << " to floor " << floorNumber << std::endl;
        }
        else
        {
            std::cout << "No elevator available for floor " << floorNumber << std::endl;
        }
    }

    void requestFloor(int elevatorId, int floorNumber)
    {
        auto elevator = getElevatorById(elevatorId);
        std::cout << "Internal request: Elevator " << elevator->getId()
                  << " to floor " << floorNumber << std::endl;

        Direction direction = floorNumber > elevator->getCurrentFloor() ? Direction::UP : Direction::DOWN;
        elevator->addRequest(
            std::make_shared<ElevatorRequest>(elevatorId, floorNumber, true, direction));
    }

    void step()
    {
        for (auto &elevator : elevators)
        {
            if (!elevator->getRequestsQueue().empty())
            {
                int nextStop = schedulingStrategy->getNextStop(elevator);
                if (elevator->getCurrentFloor() != nextStop)
                    elevator->moveToNextStop(nextStop);
            }
        }
    }

    std::vector<std::shared_ptr<Elevator>> getElevators() const { return elevators; }
    std::vector<std::shared_ptr<Floor>> getFloors() const { return floors; }
    void setCurrentElevator(int elevatorId) { this->currentElevatorId = elevatorId; }
};

class Building
{
private:
    std::string name;
    int numberOfFloors;
    std::shared_ptr<ElevatorController> elevatorController;

public:
    Building(const std::string &name, int numberOfFloors, int numberOfElevators)
        : name(name), numberOfFloors(numberOfFloors)
    {
        elevatorController = std::make_shared<ElevatorController>(numberOfElevators, numberOfFloors);
    }

    std::string getName() const { return name; }
    int getNumberOfFloors() const { return numberOfFloors; }
    std::shared_ptr<ElevatorController> getElevatorController() const { return elevatorController; }
};

// =========================== OBSERVER IMPLEMENTATIONS ===========================

void ElevatorDisplay::onElevatorStateChange(std::shared_ptr<Elevator> elevator, ElevatorState state)
{
    std::cout << "Elevator " << elevator->getId() << " state changed to ";
    switch (state)
    {
    case ElevatorState::IDLE:
        std::cout << "IDLE";
        break;
    case ElevatorState::MOVING:
        std::cout << "MOVING";
        break;
    case ElevatorState::STOPPED:
        std::cout << "STOPPED";
        break;
    case ElevatorState::MAINTENANCE:
        std::cout << "MAINTENANCE";
        break;
    }
    std::cout << std::endl;
}

void ElevatorDisplay::onElevatorFloorChange(std::shared_ptr<Elevator> elevator, int floor)
{
    std::cout << "Elevator " << elevator->getId() << " moved to floor " << floor << std::endl;
}

// =========================== UTILITY FUNCTIONS ===========================

void displayElevatorStatus(const std::vector<std::shared_ptr<Elevator>> &elevators)
{
    std::cout << "\nElevator Status:" << std::endl;
    for (auto &elevator : elevators)
    {
        std::cout << "Elevator " << elevator->getId() << ": Floor " << elevator->getCurrentFloor()
                  << ", Direction ";
        switch (elevator->getDirection())
        {
        case Direction::UP:
            std::cout << "UP";
            break;
        case Direction::DOWN:
            std::cout << "DOWN";
            break;
        case Direction::IDLE:
            std::cout << "IDLE";
            break;
        }
        std::cout << ", State ";
        switch (elevator->getState())
        {
        case ElevatorState::IDLE:
            std::cout << "IDLE";
            break;
        case ElevatorState::MOVING:
            std::cout << "MOVING";
            break;
        case ElevatorState::STOPPED:
            std::cout << "STOPPED";
            break;
        case ElevatorState::MAINTENANCE:
            std::cout << "MAINTENANCE";
            break;
        }

        auto destinations = elevator->getDestinationFloors();
        std::cout << ", Destinations [";
        for (size_t i = 0; i < destinations.size(); ++i)
        {
            std::cout << destinations[i]->getFloor();
            if (i < destinations.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

// =========================== MAIN FUNCTION ===========================

int main()
{
    // Initialize a building with 10 floors and 3 elevators
    auto building = std::make_shared<Building>("Office Tower", 10, 3);
    auto controller = building->getElevatorController();

    // Create an ElevatorDisplay to observe and display elevator events
    auto display = std::make_shared<ElevatorDisplay>();
    for (auto &elevator : controller->getElevators())
    {
        elevator->addObserver(display);
    }

    bool running = true;

    std::cout << "Elevator System Simulation" << std::endl;
    std::cout << "Building: " << building->getName() << std::endl;
    std::cout << "Floors: " << building->getNumberOfFloors() << std::endl;
    std::cout << "Elevators: " << controller->getElevators().size() << std::endl;

    while (running)
    {
        std::cout << "\nSelect an option:" << std::endl;
        std::cout << "1. Request elevator (external)" << std::endl;
        std::cout << "2. Request floor (internal)" << std::endl;
        std::cout << "3. Simulate next step" << std::endl;
        std::cout << "4. Change scheduling strategy" << std::endl;
        std::cout << "5. Exit simulation" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::cout << "Enter elevator ID: ";
            int externalElevatorId;
            std::cin >> externalElevatorId;
            controller->setCurrentElevator(externalElevatorId);

            std::cout << "Enter floor number: ";
            int floorNum;
            std::cin >> floorNum;

            std::cout << "Direction (1 for UP, 2 for DOWN): ";
            int dirChoice;
            std::cin >> dirChoice;
            Direction dir = dirChoice == 1 ? Direction::UP : Direction::DOWN;

            controller->requestElevator(externalElevatorId, floorNum, dir);
            break;
        }
        case 2:
        {
            std::cout << "Enter elevator ID: ";
            int elevatorId;
            std::cin >> elevatorId;
            controller->setCurrentElevator(elevatorId);

            std::cout << "Enter destination floor: ";
            int destFloor;
            std::cin >> destFloor;

            controller->requestFloor(elevatorId, destFloor);
            break;
        }
        case 3:
        {
            std::cout << "Simulating next step..." << std::endl;
            controller->step();
            displayElevatorStatus(controller->getElevators());
            break;
        }
        case 4:
        {
            std::cout << "Select strategy:" << std::endl;
            std::cout << "1. SCAN Algorithm" << std::endl;
            std::cout << "2. FCFS Algorithm" << std::endl;
            std::cout << "3. Look Algorithm" << std::endl;

            int strategyChoice;
            std::cin >> strategyChoice;

            if (strategyChoice == 1)
            {
                controller->setSchedulingStrategy(std::make_shared<ScanSchedulingStrategy>());
                std::cout << "Strategy set to SCAN Algorithm" << std::endl;
            }
            else if (strategyChoice == 2)
            {
                controller->setSchedulingStrategy(std::make_shared<FCFSSchedulingStrategy>());
                std::cout << "Strategy set to FCFS Algorithm" << std::endl;
            }
            else if (strategyChoice == 3)
            {
                controller->setSchedulingStrategy(std::make_shared<LookSchedulingStrategy>());
                std::cout << "Strategy set to Look Algorithm" << std::endl;
            }
            else
            {
                std::cout << "Invalid choice!" << std::endl;
            }
            break;
        }
        case 5:
            running = false;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
        }
    }

    std::cout << "Simulation ended" << std::endl;

    return 0;
}