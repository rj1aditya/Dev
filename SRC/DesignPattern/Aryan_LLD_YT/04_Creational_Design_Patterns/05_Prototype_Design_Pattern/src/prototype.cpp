#include<iostream>
#include<string>
using namespace std;

class IShape
{
    public:
    virtual IShape* clone()=0;
    virtual void draw() = 0;
};

class Circle: public IShape
{
    string color;
    public:
    Circle(string c): color(c)
    {}

    void draw()
    {
        cout << "Drawing a " << color << " Circle\n";
    }

    IShape* clone()
    {
        return new Circle(color);
    }
};

class Client
{
    public:
    IShape* prototype;
    Client(IShape* obj): prototype(obj)
    {}

    IShape* getShape()
    {
        return prototype->clone();
    }
};

int main()
{
    IShape* redCircle = new Circle("Red");
    Client c(redCircle);

    IShape* newCicle = c.getShape();
    redCircle->draw();
    newCicle->draw();

    return 0;
}