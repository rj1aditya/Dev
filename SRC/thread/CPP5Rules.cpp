#include<iostream>
using namespace std;

class X
{
    public:
    int *ptr;
    int size;
    X(int val)
    {
        size = val;
        ptr = new int[size];
    }

    virtual ~X()
    {
        delete []ptr;
        cout << "Destructor called, memory freed." << endl;
    }


    // Copy Constructor
    X(const X &obj)
    {
        size = obj.size;
        ptr = new int[size];
        for(int i = 0; i < size; i++)
            ptr[i] = obj.ptr[i];
    }

    // Copy Assignment Operator
    X& operator=(const X& obj)
    {
        if(this == &obj)
            return *this;

        delete []ptr; // Free existing resource

        size = obj.size;
        ptr = new int[size];
        for(int i = 0; i < size; i++)
            ptr[i] = obj.ptr[i];

        return *this;
    }

    // Move Constructor
    X(X&& obj) noexcept
    {
        ptr = obj.ptr;
        size = obj.size;
        obj.ptr = nullptr; // Leave obj in a valid state
        obj.size = 0;
    }

    // Move Assignment Operator
    X& operator=(X&& obj) noexcept
    {
        if(this == &obj)
            return *this;
        
        delete []ptr; // Free existing resource
        ptr = obj.ptr;
        size = obj.size;
        obj.ptr = nullptr; // Leave obj in a valid state
        obj.size = 0;
        return *this;   
    }

    void show()
    {
        cout <<"Base class show function called." << endl;  
    }
};

class A: virtual public X
{
    public:
    A(int val): X(val) {}
};

class B: virtual public X
{
    public:
    B(): X(0) {}
};

class C: public A, public B
{
    public:
    C(int val): A(val), B(), X(val) {}
};

int main()
{
    C obj(10);
    obj.show();
    return 0;
}


//what is virtual inheritance? Explain with an example.