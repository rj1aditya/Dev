#include <iostream>
#include <string>
#include <memory>

using namespace std;

// ============================================
// Step 1: Define the Component Interface
// ============================================
class BasePizza
{
public:
    virtual ~BasePizza() = default;
    virtual string getDescription() const = 0;
    virtual double getCost() const = 0;
};

// ============================================
// Step 2: Define the Concrete Components
// ============================================
class PlainPizza : public BasePizza
{
public:
    string getDescription() const override
    {
        return "Plain Pizza";
    }

    double getCost() const override
    {
        return 200.00;
    }
};

class Farmhouse : public BasePizza
{
public:
    string getDescription() const override
    {
        return "Farmhouse Pizza";
    }

    double getCost() const override
    {
        return 300.0;
    }
};

class TandooriPaneerDelight : public BasePizza
{
public:
    string getDescription() const override
    {
        return "Tandoori Paneer Delight Pizza";
    }

    double getCost() const override
    {
        return 400.0;
    }
};

// ============================================
// Step 3: Define the Abstract Base Decorator
// ============================================
class ToppingDecorator : public BasePizza
{
protected:
    shared_ptr<BasePizza> pizza;

public:
    ToppingDecorator(shared_ptr<BasePizza> p) : pizza(p) {}
    virtual ~ToppingDecorator() = default;
};

// ============================================
// Step 4: Define the Concrete Decorators
// ============================================
class ExtraCheeseTopping : public ToppingDecorator
{
public:
    ExtraCheeseTopping(shared_ptr<BasePizza> p) : ToppingDecorator(p) {}

    string getDescription() const override
    {
        return pizza->getDescription() + " + Extra Cheese";
    }

    double getCost() const override
    {
        return pizza->getCost() + 20;
    }
};

class MushroomTopping : public ToppingDecorator
{
public:
    MushroomTopping(shared_ptr<BasePizza> p) : ToppingDecorator(p) {}

    string getDescription() const override
    {
        return pizza->getDescription() + " + Mushroom";
    }

    double getCost() const override
    {
        return pizza->getCost() + 40;
    }
};

class PepperoniTopping : public ToppingDecorator
{
public:
    PepperoniTopping(shared_ptr<BasePizza> p) : ToppingDecorator(p) {}

    string getDescription() const override
    {
        return pizza->getDescription() + " + Pepperoni";
    }

    double getCost() const override
    {
        return pizza->getCost() + 50;
    }
};

class VeggiesTopping : public ToppingDecorator
{
public:
    VeggiesTopping(shared_ptr<BasePizza> p) : ToppingDecorator(p) {}

    string getDescription() const override
    {
        return pizza->getDescription() + " + Veggies";
    }

    double getCost() const override
    {
        return pizza->getCost() + 30;
    }
};

// ============================================
// Step 5: Client Demonstration
// ============================================
int main()
{
    cout << "======= Decorator Design Pattern ======" << endl;

    // Order 1: Plain Pizza
    shared_ptr<BasePizza> pizza1 = make_shared<PlainPizza>();
    cout << "Order 1: " << pizza1->getDescription() << " = Rs." << pizza1->getCost() << endl;

    // Order 2: Plain Pizza with Extra Cheese
    shared_ptr<BasePizza> pizza2 = make_shared<ExtraCheeseTopping>(
        make_shared<PlainPizza>());
    cout << "Order 2: " << pizza2->getDescription() << " = Rs." << pizza2->getCost() << endl;

    // Order 3: Plain Pizza with Extra Cheese and Veggies
    shared_ptr<BasePizza> pizza3 = make_shared<VeggiesTopping>(
        make_shared<ExtraCheeseTopping>(make_shared<PlainPizza>()));
    cout << "Order 3: " << pizza3->getDescription() << " = Rs." << pizza3->getCost() << endl;

    // Order 4: Plain Pizza with Extra Cheese and Pepperoni
    shared_ptr<BasePizza> pizza4 = make_shared<PepperoniTopping>(
        make_shared<ExtraCheeseTopping>(make_shared<PlainPizza>()));
    cout << "Order 4: " << pizza4->getDescription() << " = Rs." << pizza4->getCost() << endl;

    // Order 5: Plain Pizza with Extra Cheese, Mushroom and Pepperoni
    shared_ptr<BasePizza> pizza5 = make_shared<MushroomTopping>(
        make_shared<PepperoniTopping>(
            make_shared<ExtraCheeseTopping>(make_shared<PlainPizza>())));
    cout << "Order 5: " << pizza5->getDescription() << " = Rs." << pizza5->getCost() << endl;

    // Order 6: Farmhouse Pizza
    shared_ptr<BasePizza> pizza6 = make_shared<Farmhouse>();
    cout << "Order 6: " << pizza6->getDescription() << " = Rs." << pizza6->getCost() << endl;

    // Order 7: Farmhouse Pizza with Extra Cheese and Mushroom
    shared_ptr<BasePizza> pizza7 = make_shared<MushroomTopping>(
        make_shared<ExtraCheeseTopping>(make_shared<Farmhouse>()));
    cout << "Order 7: " << pizza7->getDescription() << " = Rs." << pizza7->getCost() << endl;

    // Order 8: Tandoori Paneer Delight Pizza
    shared_ptr<BasePizza> pizza8 = make_shared<TandooriPaneerDelight>();
    cout << "Order 8: " << pizza8->getDescription() << " = Rs." << pizza8->getCost() << endl;

    // Order 9: Chicken Dominator Pizza
    shared_ptr<BasePizza> pizza9 = make_shared<ChickenDominator>();
    cout << "Order 9: " << pizza9->getDescription() << " = Rs." << pizza9->getCost() << endl;

    // Order 10: Chicken Dominator with Mushroom
    shared_ptr<BasePizza> pizza10 = make_shared<MushroomTopping>(
        make_shared<ChickenDominator>());
    cout << "Order 10: " << pizza10->getDescription() << " = Rs." << pizza10->getCost() << endl;

    return 0;
}
