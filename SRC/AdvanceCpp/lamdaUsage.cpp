#include <iostream>
#include <functional>

class Demo
{
public:
    int value = 10;

    void lambdaWithThis()
    {
        auto func1 = [this]()
        {
            std::cout << "Using [this]: value = " << value << std::endl;
            value = 20; // Modifies original object
        };

        auto func2 = [*this]() mutable
        {
            std::cout << "Using [*this]: value = " << value << std::endl;
            value = 30; // Modifies copy, NOT original object
        };

        func1();
        func2();

        std::cout << "Original value after lambda calls: " << value << std::endl;
    }
};

int main()
{
    Demo obj;
    obj.lambdaWithThis();
    return 0;
}