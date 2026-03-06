#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
public:
    virtual void printVehicle() = 0;
    virtual ~Vehicle() {}
};

class Car : public Vehicle
{
public:
    ~Car() {}
    void printVehicle() override
    {
        cout << "This is a Car" << endl;
    }
};

class Bike : public Vehicle
{
public:
    ~Bike(){}
    void printVehicle() override
    {
        cout << "This is a Bike" << endl;
    }
};

class VehicleFactory
{
public:
    virtual Vehicle *createVehicle() = 0;
    virtual ~VehicleFactory() {}
};

class CarFactory : public VehicleFactory
{
public:
    Vehicle *createVehicle() override
    {
        return new Car();
    }
    ~CarFactory() {}
};

class BikeFactory : public VehicleFactory
{
    public:
    Vehicle* createVehicle() override
    {
        return new Bike();
    }
    ~BikeFactory() {}
};

class Client
{
    Vehicle* vehcle;
    public:
    Client(VehicleFactory *factory)
    {
        vehcle = factory->createVehicle();
    }

    void print()
    {
        vehcle->printVehicle();
    }

    ~Client()
    {
        delete vehcle;
    }
};

int main()
{
    CarFactory *cf = new CarFactory();
    Client c(cf);
    c.print();

    BikeFactory *bf = new BikeFactory();
    Client d(bf);
    d.print();
}