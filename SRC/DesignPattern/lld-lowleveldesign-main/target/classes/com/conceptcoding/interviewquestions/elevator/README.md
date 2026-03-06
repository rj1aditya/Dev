# Elevator System - C++ Implementation

## Overview

This is a comprehensive elevator system implementation converted from Java to C++ that demonstrates various design patterns including Strategy, Observer, Command, and Singleton patterns.

## Features

### Design Patterns Implemented

- **Strategy Pattern**: Multiple elevator selection algorithms (NearestElevator, LeastBusy)
- **Singleton Pattern**: InternalDispatcher for internal button requests
- **Command Pattern**: Button classes that dispatch elevator requests
- **Observer/Publisher Pattern**: Coordination between dispatchers and controllers

### Key Components

#### Core Classes

- **ElevatorCar**: Represents physical elevator with movement and door operations
- **ElevatorController**: Manages elevator requests using priority queues (UP/DOWN)
- **Door**: Controls elevator door state (open/closed) with visual feedback
- **Floor**: Represents building floors with up/down call buttons
- **Building**: Manages all floors and external dispatcher integration

#### Strategy Classes

- **NearestElevatorStrategy**: Selects elevator based on proximity and direction
- **LeastBusyStrategy**: Selects elevator with lowest request queue size

#### Dispatcher Classes

- **ExternalDispatcher**: Handles external floor-to-floor requests
- **InternalDispatcher**: Singleton handling internal cabin button presses

#### Button Classes

- **ExternalButton**: Floor call buttons (UP/DOWN)
- **InternalButton**: Cabin destination selection buttons

#### Scheduler

- **ElevatorScheduler**: Coordinates elevator assignment using selected strategy

### Threading Model

- Each elevator controller runs in its own thread
- Thread-safe priority queues for UP/DOWN requests
- Mutex protection with condition variables for synchronization
- Atomic operations for elevator state management

### Compilation and Execution

```bash
# Compile
g++ -std=c++17 -Wall -Wextra -g elevatorSystem.cpp -o elevatorSystem

# Run
./elevatorSystem
```

### Demo Features

1. Multiple simultaneous elevator requests
2. External floor calls (UP/DOWN buttons)
3. Internal cabin destination requests
4. Dynamic strategy switching during runtime
5. Real-time elevator movement visualization
6. Thread-safe concurrent operation

### System Behavior

- Elevators optimize routes using priority queues (min-heap for UP, max-heap for DOWN)
- Smart elevator selection based on direction and proximity
- Visual feedback for door operations and floor transitions
- Graceful shutdown with thread cleanup

### Technical Highlights

- Modern C++17 features (smart pointers, atomic operations, chrono)
- Exception-safe RAII resource management
- Zero memory leaks with automatic cleanup
- Comprehensive design pattern implementation
- Realistic elevator timing with movement delays

## System Output Example

```
=== Starting Elevator System Demo ===
1. External Call: Floor 3 UP
Request details-> destinationFloor: 3 accepted by elevator:1
Serving floor: 3 by elevator:1 currentFloor: 0
Closing the Elevator door of elevator:1
elevator:1 Current floor: 0 going: UP
elevator:1 Current floor: 1 going: UP
...
```

This system demonstrates a production-ready elevator control system with proper concurrency, design patterns, and modern C++ practices.
