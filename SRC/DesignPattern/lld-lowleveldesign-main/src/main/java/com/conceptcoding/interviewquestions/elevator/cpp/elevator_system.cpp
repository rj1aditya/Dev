/*
object identification:
1. building
2. floor
3. elevator
4. elevator controller - it will have the elevator moving behaviour logic, we will implement the look algorithm using min 
and max pq.
5. external button
6. internal button
7. external dispatcher - who will select the elevator scheduler, external dispatcher selects the elevator scheduler
8. elevator schedueler - who will select the elevator controller, scheduler selects the elevator controller 
using elevatorselection strategy.
    a. nearest elevator selection strategy [child class of elevatorselectionstrategy]
    b. least busy elevator selection strategy [child class of elevatorselectionstrategy]
9. internal dispatcher
*/


#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <unordered_map>
#include <set>
#include <limits>
#include <algorithm>

using namespace std;


#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <chrono>

// Forward declarations
class ExternalDispatcher;
class Floor;
class ElevatorScheduler;
class ElevatorController;
class ElevatorSelectionStrategy;
class InternalDispatcher;

// ------------------------------------------
enum class ElevatorDirection {
    UP,
    DOWN,
    IDLE
};

// ------------------------------------------
// Door class
// ------------------------------------------
class Door {
public:
    void openDoor(int id) {
        cout << "Elevator " << id << ": Door Open\n";
    }

    void closeDoor(int id) {
        cout << "Elevator " << id << ": Door Close\n";
    }
};

 // ------------------------------------------
// ElevatorCar (converted from Java)
// ------------------------------------------
class ElevatorCar {
public:
    int id;
    int currentFloor;
    int nextFloorStoppage;
    ElevatorDirection movingDirection;
    Door door;

    ElevatorCar(int id) {
        this->id = id;
        currentFloor = 0;
        nextFloorStoppage = 0;
        movingDirection = ElevatorDirection::IDLE;
    }

    void showDisplay() {
        cout << "Elevator:" << id
             << " Current floor: " << currentFloor
             << " going: " << directionToString(movingDirection)
             << "\n";
    }

    void moveElevator(int destinationFloor) {
        // This is a dumb object: if command received, it moves directly
        // regardless of current state or logic.

        this->nextFloorStoppage = destinationFloor;

        if (this->currentFloor == nextFloorStoppage) {
            door.openDoor(id);
            return;
        }

        int startFloor = this->currentFloor;
        door.closeDoor(id);

        if (nextFloorStoppage >= currentFloor) {
            movingDirection = ElevatorDirection::UP;
            showDisplay();

            for (int i = startFloor + 1; i <= nextFloorStoppage; i++) {
                this_thread::sleep_for(chrono::milliseconds(5));
                setCurrentFloor(i);
                showDisplay();
            }
        } else {
            movingDirection = ElevatorDirection::DOWN;
            showDisplay();

            for (int i = startFloor - 1; i >= nextFloorStoppage; i--) {
                this_thread::sleep_for(chrono::milliseconds(5));
                setCurrentFloor(i);
                showDisplay();
            }
        }

        door.openDoor(id);
    }

    void setCurrentFloor(int currentFloor) {
        this->currentFloor = currentFloor;
    }

private:
    string directionToString(ElevatorDirection d) {
        switch (d) {
            case ElevatorDirection::UP:   return "UP";
            case ElevatorDirection::DOWN: return "DOWN";
            case ElevatorDirection::IDLE: return "IDLE";
        }
        return "UNKNOWN";
    }
};

class ElevatorController {
public:
    // -------------------------
    // Priority Queues 
    // -------------------------

    // Min-heap for UP direction
    priority_queue<int, vector<int>, greater<int>> upMinPQ;

    // Max-heap for DOWN direction
    priority_queue<int> downMaxPQ;

    ElevatorCar* elevatorCar;

    // monitor equivalent
    mutex mtx;
    condition_variable cv;
    atomic<bool> stopFlag{false};

    ElevatorController(ElevatorCar* elevatorCar) {
        this->elevatorCar = elevatorCar;
    }

    void submitRequest(int destinationFloor) {
        enqueueRequest(destinationFloor);
    }

private:
    void enqueueRequest(int destinationFloor) {

        cout << "Request details-> destinationFloor: "
             << destinationFloor
             << " accepted by elevator:" << elevatorCar->id
             << "\n";

        // Same condition as Java
        if (destinationFloor == elevatorCar->nextFloorStoppage) {
            return;
        }

        if (destinationFloor >= elevatorCar->nextFloorStoppage) {
            // Java: if (!upMinPQ.contains())
            if (!contains(upMinPQ, destinationFloor)) {
                upMinPQ.push(destinationFloor);
            }
        } else {
            if (!contains(downMaxPQ, destinationFloor)) {
                downMaxPQ.push(destinationFloor);
            }
        }

        cv.notify_one(); // wake sleeping controller
    }

    // Utility: check if priority_queue contains an element
    template<typename PQ>
    bool contains(PQ pqCopy, int x) {
        while (!pqCopy.empty()) {
            if (pqCopy.top() == x) return true;
            pqCopy.pop();
        }
        return false;
    }

public:

    // Equivalent to Java's run()
    void run() {
        controlElevator();
    }

    void controlElevator() {
        while (!stopFlag.load()) {
            // ---------------------------
            // If no requests, sleep
            // ---------------------------
            {
                unique_lock<mutex> lock(mtx);
                while (upMinPQ.empty() && downMaxPQ.empty()) {
                    cout << "elevator:" << elevatorCar->id << " is IDLE\n";
                    elevatorCar->movingDirection = ElevatorDirection::IDLE;
                    cv.wait(lock);  // wait for new request
                }
            }

            // ---------------------------
            // Process UP queue (min PQ)
            // ---------------------------
            while (!upMinPQ.empty()) {
                int floor = upMinPQ.top();
                upMinPQ.pop();

                cout << "Serving floor: " << floor
                     << " by elevator:" << elevatorCar->id
                     << " currentFloor: " << elevatorCar->currentFloor
                     << "\n";

                elevatorCar->moveElevator(floor);
            }

            // ---------------------------
            // Process DOWN queue (max PQ)
            // ---------------------------
            while (!downMaxPQ.empty()) {
                int floor = downMaxPQ.top();
                downMaxPQ.pop();

                cout << "Serving floor: " << floor
                     << " by elevator:" << elevatorCar->id
                     << " currentFloor: " << elevatorCar->currentFloor
                     << "\n";

                elevatorCar->moveElevator(floor);
            }
        }
    }

    void stop() {
        stopFlag = true;
        cv.notify_one();
    }
};

class ElevatorSelectionStrategy {
public:
    virtual ElevatorController* selectElevator(
        const vector<ElevatorController*>& controllers,
        int requestFloor,
        ElevatorDirection direction
    ) = 0;

    virtual ~ElevatorSelectionStrategy() = default;
};

class LeastBusyStrategy : public ElevatorSelectionStrategy {
public:
    ElevatorController* selectElevator(
        const vector<ElevatorController*>& controllers,
        int requestFloor,
        ElevatorDirection direction
    ) override 
    {
        ElevatorController* best = nullptr;
        int minLoad = INT_MAX;

        for (auto* controller : controllers) {
            int load =
                controller->upMinPQ.size() +
                controller->downMaxPQ.size();

            if (load < minLoad) {
                minLoad = load;
                best = controller;
            }
        }
        return best;
    }
};

class NearestElevatorStrategy : public ElevatorSelectionStrategy {
public:
    ElevatorController* selectElevator(
        const vector<ElevatorController*>& controllers,
        int requestFloor,
        ElevatorDirection direction
    ) override 
    {
        ElevatorController* best = nullptr;
        int minDistance = INT_MAX;

        // Step 1: choose elevator going in same direction and not passed requested floor
        for (auto* controller : controllers) {

            int nextFloorStoppage = controller->elevatorCar->nextFloorStoppage;

            bool isSameDirectionCandidate =
                (controller->elevatorCar->movingDirection == direction) &&
                (
                    (direction == ElevatorDirection::UP &&
                     nextFloorStoppage <= requestFloor)
                    ||
                    (direction == ElevatorDirection::DOWN &&
                     nextFloorStoppage >= requestFloor)
                );

            int dist = abs(nextFloorStoppage - requestFloor);

            if (isSameDirectionCandidate && dist < minDistance) {
                minDistance = dist;
                best = controller;
            }
        }

        // Step 2: fallback — pick idle elevator
        if (best == nullptr) {
            for (auto* controller : controllers) {
                if (controller->elevatorCar->movingDirection == ElevatorDirection::IDLE) {
                    best = controller;
                    break;
                }
            }
        }

        // Step 3: fallback — pick first elevator
        if (best == nullptr && !controllers.empty()) {
            best = controllers[0];
        }

        return best;
    }
};

class ElevatorScheduler {
private:
    vector<ElevatorController*> controllers;
    ElevatorSelectionStrategy* strategy;

public:
    ElevatorScheduler(const vector<ElevatorController*>& controllers,
                      ElevatorSelectionStrategy* strategy)
        : controllers(controllers), strategy(strategy) {}

    void setStrategy(ElevatorSelectionStrategy* newStrategy) {
        strategy = newStrategy;
    }

    ElevatorController* assignElevator(int floor, ElevatorDirection direction) {
        return strategy->selectElevator(controllers, floor, direction);
    }
};

class ExternalDispatcher {
private:
    ElevatorScheduler* scheduler;

public:
    ExternalDispatcher(ElevatorScheduler* scheduler)
        : scheduler(scheduler) {}

    void submitExternalRequest(int floor, ElevatorDirection direction) {
        ElevatorController* controller =
            scheduler->assignElevator(floor, direction);

        controller->submitRequest(floor);
    }
};

class ExternalButton {
private:
    ExternalDispatcher* dispatcher;

public:
    ExternalButton(ExternalDispatcher* dispatcher)
        : dispatcher(dispatcher) {}

    // same logic as Java version
    void pressButton(int floor, ElevatorDirection direction) {
        dispatcher->submitExternalRequest(floor, direction);
    }
};

class Floor {
private:
    int floorNumber;
    ExternalButton* upButton;
    ExternalButton* downButton;

public:
    Floor(int floorNumber, ExternalDispatcher* dispatcher)
        : floorNumber(floorNumber)
    {
        upButton = new ExternalButton(dispatcher);
        downButton = new ExternalButton(dispatcher);
    }

    void pressUpButton() {
        upButton->pressButton(floorNumber, ElevatorDirection::UP);
    }

    void pressDownButton() {
        downButton->pressButton(floorNumber, ElevatorDirection::DOWN);
    }
};

class Building {
private:
    vector<Floor*> floors;

public:
    Building(int totalFloors, ExternalDispatcher* dispatcher) {
        floors.reserve(totalFloors);
        for (int i = 1; i <= totalFloors; i++) {
            floors.push_back(new Floor(i, dispatcher));
        }
    }

    Floor* getFloor(int floor) {
        return floors[floor - 1];
    }
};
class InternalDispatcher {
private:
    // Singleton instance
    static InternalDispatcher* INSTANCE;

    // Private constructor
    InternalDispatcher() {}

public:
    // Get singleton instance
    static InternalDispatcher* getInstance() {
        if (INSTANCE == nullptr) {
            INSTANCE = new InternalDispatcher();
        }
        return INSTANCE;
    }

    // Submit internal request to correct elevator controller
    void submitInternalRequest(int destinationFloor, ElevatorController* controller) {
        controller->submitRequest(destinationFloor);
    }
};

// Define static member
InternalDispatcher* InternalDispatcher::INSTANCE = nullptr;

class InternalButton {
private:
    ElevatorController* controller;

public:
    InternalButton(ElevatorController* controller)
        : controller(controller) {}

    void pressButton(int destinationFloor) {
        // same flow as Java version
        InternalDispatcher::getInstance()
            ->submitInternalRequest(destinationFloor, controller);
    }
};

int main() {
    // 1. Create elevator cars + controllers
    ElevatorCar car1(1);
    ElevatorController controller1(&car1);

    ElevatorCar car2(2);
    ElevatorController controller2(&car2);

    // 2. Create internal buttons
    InternalButton internalButton1(&controller1);
    InternalButton internalButton2(&controller2);

    // 3. Scheduler with nearest strategy
    NearestElevatorStrategy strat;
    ElevatorScheduler scheduler({&controller1, &controller2}, &strat);

    // 4. External dispatcher
    ExternalDispatcher dispatcher(&scheduler);

    // 5. Building
    Building building(5, &dispatcher);

    // 6. Start controller threads
    thread t1(&ElevatorController::run, &controller1);
    thread t2(&ElevatorController::run, &controller2);

    // Same sequence as Java code
    building.getFloor(3)->pressUpButton();
    this_thread::sleep_for(chrono::milliseconds(5));

    building.getFloor(5)->pressDownButton();
    this_thread::sleep_for(chrono::milliseconds(5));

    internalButton1.pressButton(4);
    this_thread::sleep_for(chrono::milliseconds(5));

    internalButton1.pressButton(5);
    this_thread::sleep_for(chrono::milliseconds(5));

    building.getFloor(1)->pressDownButton();
    this_thread::sleep_for(chrono::milliseconds(5));

    building.getFloor(2)->pressUpButton();
    this_thread::sleep_for(chrono::milliseconds(5));

    internalButton1.pressButton(2);

    // Allow time for elevators to finish tasks
    this_thread::sleep_for(chrono::seconds(2));

    // Stop threads
    controller1.stop();
    controller2.stop();

    t1.join();
    t2.join();

    return 0;
}