#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <chrono>
#include <mutex>
#include <algorithm>
#include <stdexcept>

// =========================== ENUMS ===========================

enum class VehicleType
{
    TWO_WHEELER,
    FOUR_WHEELER
};

// =========================== FORWARD DECLARATIONS ===========================

class ParkingLevel;

// =========================== BASIC CLASSES ===========================

class ParkingSpot
{
private:
    const std::string spotId;
    bool isFree = true;

public:
    ParkingSpot(const std::string &spotId) : spotId(spotId) {}

    bool isSpotFree() const
    {
        return isFree;
    }

    void occupySpot()
    {
        isFree = false;
    }

    void releaseSpot()
    {
        isFree = true;
    }

    std::string getSpotId() const
    {
        return spotId;
    }
};

class Vehicle
{
private:
    std::string vehicleNumber;
    VehicleType vehicleType;

public:
    Vehicle(const std::string &vehicleNumber, VehicleType vehicleType)
        : vehicleNumber(vehicleNumber), vehicleType(vehicleType) {}

    std::string getVehicleNumber() const
    {
        return vehicleNumber;
    }

    VehicleType getVehicleType() const
    {
        return vehicleType;
    }
};

class Ticket
{
private:
    std::shared_ptr<Vehicle> vehicle;
    std::shared_ptr<ParkingLevel> level;
    std::shared_ptr<ParkingSpot> spot;
    std::chrono::system_clock::time_point entryTime;

public:
    Ticket(std::shared_ptr<Vehicle> vehicle,
           std::shared_ptr<ParkingLevel> level,
           std::shared_ptr<ParkingSpot> spot)
        : vehicle(vehicle), level(level), spot(spot), entryTime(std::chrono::system_clock::now()) {}

    std::shared_ptr<Vehicle> getVehicle() const
    {
        return vehicle;
    }

    std::shared_ptr<ParkingLevel> getLevel() const
    {
        return level;
    }

    std::shared_ptr<ParkingSpot> getSpot() const
    {
        return spot;
    }

    std::chrono::system_clock::time_point getEntryTime() const
    {
        return entryTime;
    }
};

// =========================== STRATEGY INTERFACES ===========================

class Payment
{
public:
    virtual ~Payment() = default;
    virtual bool pay(double amount) = 0;
};

class PricingStrategy
{
public:
    virtual ~PricingStrategy() = default;
    virtual double calculate(std::shared_ptr<Ticket> ticket) = 0;
};

class ParkingSpotLookupStrategy
{
public:
    virtual ~ParkingSpotLookupStrategy() = default;
    virtual std::shared_ptr<ParkingSpot> selectSpot(const std::vector<std::shared_ptr<ParkingSpot>> &spots) = 0;
};

// =========================== CONCRETE STRATEGY IMPLEMENTATIONS ===========================

class CashPayment : public Payment
{
public:
    bool pay(double amount) override
    {
        std::cout << "Cash paid: " << amount << std::endl;
        return true;
    }
};

class UPIPayment : public Payment
{
public:
    bool pay(double amount) override
    {
        std::cout << "UPI paid: " << amount << std::endl;
        return true;
    }
};

class FixedPricingStrategy : public PricingStrategy
{
public:
    double calculate(std::shared_ptr<Ticket> ticket) override
    {
        return 100.0;
    }
};

class RandomLookupStrategy : public ParkingSpotLookupStrategy
{
public:
    std::shared_ptr<ParkingSpot> selectSpot(const std::vector<std::shared_ptr<ParkingSpot>> &spots) override
    {
        for (const auto &spot : spots)
        {
            if (spot->isSpotFree())
            {
                return spot;
            }
        }
        return nullptr;
    }
};

// =========================== COST COMPUTATION ===========================

class CostComputation
{
private:
    std::shared_ptr<PricingStrategy> pricingStrategy;

public:
    CostComputation(std::shared_ptr<PricingStrategy> pricingStrategy)
        : pricingStrategy(pricingStrategy) {}

    double compute(std::shared_ptr<Ticket> ticket)
    {
        return pricingStrategy->calculate(ticket);
    }
};

// =========================== MANAGER CLASSES ===========================

class ParkingSpotManager
{
protected:
    std::vector<std::shared_ptr<ParkingSpot>> spots;
    std::shared_ptr<ParkingSpotLookupStrategy> strategy;
    std::mutex lock;

public:
    ParkingSpotManager(const std::vector<std::shared_ptr<ParkingSpot>> &spots,
                       std::shared_ptr<ParkingSpotLookupStrategy> strategy)
        : spots(spots), strategy(strategy) {}

    virtual ~ParkingSpotManager() = default;

    std::shared_ptr<ParkingSpot> park()
    {
        std::lock_guard<std::mutex> guard(lock);

        auto spot = strategy->selectSpot(spots);
        if (spot == nullptr)
        {
            return nullptr;
        }

        spot->occupySpot();
        return spot;
    }

    void unPark(std::shared_ptr<ParkingSpot> spot)
    {
        std::lock_guard<std::mutex> guard(lock);
        spot->releaseSpot();
    }

    bool hasFreeSpot()
    {
        std::lock_guard<std::mutex> guard(lock);
        return std::any_of(spots.begin(), spots.end(),
                           [](const auto &spot)
                           { return spot->isSpotFree(); });
    }
};

class TwoWheelerSpotManager : public ParkingSpotManager
{
public:
    TwoWheelerSpotManager(const std::vector<std::shared_ptr<ParkingSpot>> &spots,
                          std::shared_ptr<ParkingSpotLookupStrategy> strategy)
        : ParkingSpotManager(spots, strategy) {}
};

class FourWheelerSpotManager : public ParkingSpotManager
{
public:
    FourWheelerSpotManager(const std::vector<std::shared_ptr<ParkingSpot>> &spots,
                           std::shared_ptr<ParkingSpotLookupStrategy> strategy)
        : ParkingSpotManager(spots, strategy) {}
};

// =========================== PARKING LEVEL ===========================

class ParkingLevel
{
private:
    const int levelNumber;
    std::map<VehicleType, std::shared_ptr<ParkingSpotManager>> managers;

public:
    ParkingLevel(int levelNumber,
                 const std::map<VehicleType, std::shared_ptr<ParkingSpotManager>> &managers)
        : levelNumber(levelNumber), managers(managers) {}

    bool hasAvailability(VehicleType type)
    {
        auto it = managers.find(type);
        return it != managers.end() && it->second != nullptr && it->second->hasFreeSpot();
    }

    std::shared_ptr<ParkingSpot> park(VehicleType type)
    {
        auto it = managers.find(type);
        if (it == managers.end() || it->second == nullptr)
        {
            throw std::invalid_argument("No parking manager for vehicle type");
        }
        return it->second->park();
    }

    void unPark(VehicleType type, std::shared_ptr<ParkingSpot> spot)
    {
        auto it = managers.find(type);
        if (it != managers.end() && it->second != nullptr)
        {
            it->second->unPark(spot);
        }
    }

    int getLevelNumber() const
    {
        return levelNumber;
    }
};

// =========================== PARKING BUILDING ===========================

class ParkingBuilding
{
private:
    std::vector<std::shared_ptr<ParkingLevel>> levels;
    std::shared_ptr<CostComputation> costComputation;

public:
    ParkingBuilding(const std::vector<std::shared_ptr<ParkingLevel>> &levels,
                    std::shared_ptr<CostComputation> costComputation)
        : levels(levels), costComputation(costComputation) {}

    std::shared_ptr<Ticket> allocate(std::shared_ptr<Vehicle> vehicle)
    {
        for (auto &level : levels)
        {
            if (level->hasAvailability(vehicle->getVehicleType()))
            {
                auto spot = level->park(vehicle->getVehicleType());
                if (spot != nullptr)
                {
                    auto ticket = std::make_shared<Ticket>(vehicle, level, spot);
                    std::cout << "Parking allocated at level: " << level->getLevelNumber()
                              << " spot: " << spot->getSpotId() << std::endl;
                    return ticket;
                }
            }
        }
        throw std::runtime_error("Parking Full");
    }

    void release(std::shared_ptr<Ticket> ticket)
    {
        ticket->getLevel()->unPark(ticket->getVehicle()->getVehicleType(),
                                   ticket->getSpot());
    }
};

// =========================== GATES ===========================

class EntranceGate
{
public:
    std::shared_ptr<Ticket> enter(std::shared_ptr<ParkingBuilding> building,
                                  std::shared_ptr<Vehicle> vehicle)
    {
        return building->allocate(vehicle);
    }
};

class ExitGate
{
private:
    std::shared_ptr<CostComputation> costComputation;

    double calculatePrice(std::shared_ptr<Ticket> ticket)
    {
        return costComputation->compute(ticket);
    }

public:
    ExitGate(std::shared_ptr<CostComputation> costComputation)
        : costComputation(costComputation) {}

    void completeExit(std::shared_ptr<ParkingBuilding> building,
                      std::shared_ptr<Ticket> ticket,
                      std::shared_ptr<Payment> payment)
    {
        double amount = calculatePrice(ticket);

        bool success = payment->pay(amount);
        if (!success)
        {
            throw std::runtime_error("Payment failed. Exit denied.");
        }

        building->release(ticket);
        std::cout << "Exit successful. Gate opened." << std::endl;
    }
};

// =========================== MAIN PARKING LOT SYSTEM ===========================

class ParkingLot
{
private:
    std::shared_ptr<ParkingBuilding> building;
    std::shared_ptr<EntranceGate> entranceGate;
    std::shared_ptr<ExitGate> exitGate;

public:
    ParkingLot(std::shared_ptr<ParkingBuilding> building,
               std::shared_ptr<EntranceGate> entranceGate,
               std::shared_ptr<ExitGate> exitGate)
        : building(building), entranceGate(entranceGate), exitGate(exitGate) {}

    std::shared_ptr<Ticket> vehicleArrives(std::shared_ptr<Vehicle> vehicle)
    {
        return entranceGate->enter(building, vehicle);
    }

    void vehicleExits(std::shared_ptr<Ticket> ticket, std::shared_ptr<Payment> payment)
    {
        exitGate->completeExit(building, ticket, payment);
    }
};

// =========================== MAIN FUNCTION ===========================

int main()
{
    // Create parking spot lookup strategy
    auto strategy = std::make_shared<RandomLookupStrategy>();

    // Create parking spots for level 1
    std::vector<std::shared_ptr<ParkingSpot>> level1TwoWheelerSpots = {
        std::make_shared<ParkingSpot>("L1-S1"),
        std::make_shared<ParkingSpot>("L1-S2")};

    std::vector<std::shared_ptr<ParkingSpot>> level1FourWheelerSpots = {
        std::make_shared<ParkingSpot>("L1-S3")};

    // Create managers for level 1
    std::map<VehicleType, std::shared_ptr<ParkingSpotManager>> levelOneManagers;
    levelOneManagers[VehicleType::TWO_WHEELER] =
        std::make_shared<TwoWheelerSpotManager>(level1TwoWheelerSpots, strategy);
    levelOneManagers[VehicleType::FOUR_WHEELER] =
        std::make_shared<FourWheelerSpotManager>(level1FourWheelerSpots, strategy);

    // Create parking level 1
    auto level1 = std::make_shared<ParkingLevel>(1, levelOneManagers);

    // Create parking spots for level 2
    std::vector<std::shared_ptr<ParkingSpot>> level2TwoWheelerSpots = {
        std::make_shared<ParkingSpot>("L2-S1")};

    std::vector<std::shared_ptr<ParkingSpot>> level2FourWheelerSpots = {
        std::make_shared<ParkingSpot>("L2-S2"),
        std::make_shared<ParkingSpot>("L2-S3")};

    // Create managers for level 2
    std::map<VehicleType, std::shared_ptr<ParkingSpotManager>> levelTwoManagers;
    levelTwoManagers[VehicleType::TWO_WHEELER] =
        std::make_shared<TwoWheelerSpotManager>(level2TwoWheelerSpots, strategy);
    levelTwoManagers[VehicleType::FOUR_WHEELER] =
        std::make_shared<FourWheelerSpotManager>(level2FourWheelerSpots, strategy);

    // Create parking level 2
    auto level2 = std::make_shared<ParkingLevel>(2, levelTwoManagers);

    // Create pricing strategy and cost computation
    auto pricingStrategy = std::make_shared<FixedPricingStrategy>();
    auto costComputation = std::make_shared<CostComputation>(pricingStrategy);

    // Create parking building
    std::vector<std::shared_ptr<ParkingLevel>> levels = {level1, level2};
    auto parkingBuilding = std::make_shared<ParkingBuilding>(levels, costComputation);

    // Create gates
    auto entranceGate = std::make_shared<EntranceGate>();
    auto exitGate = std::make_shared<ExitGate>(costComputation);

    // Create parking lot
    auto parkingLot = std::make_shared<ParkingLot>(parkingBuilding, entranceGate, exitGate);

    // Create vehicles
    auto bike = std::make_shared<Vehicle>("BIKE-101", VehicleType::TWO_WHEELER);
    auto car = std::make_shared<Vehicle>("CAR-201", VehicleType::FOUR_WHEELER);

    // Test parking lot functionality
    std::cout << "=== Testing Parking Lot System ===" << std::endl;

    // Vehicles arrive
    std::cout << "\nVehicles arriving..." << std::endl;
    auto t1 = parkingLot->vehicleArrives(bike);
    auto t2 = parkingLot->vehicleArrives(car);

    // Vehicles exit
    std::cout << "\nVehicles exiting..." << std::endl;
    auto cashPayment = std::make_shared<CashPayment>();
    auto upiPayment = std::make_shared<UPIPayment>();

    parkingLot->vehicleExits(t1, cashPayment);
    parkingLot->vehicleExits(t2, upiPayment);

    std::cout << "\n=== Test completed successfully ===" << std::endl;

    return 0;
}