#ifndef ARRAY_H
#define ARRAY_H

#include<iostream>
using namespace std;

template <typename T>

class Array
{
    int length;
    T* arr;
    public:
    Array(int len): length(len){
        arr = new T[length]{};
    }

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    ~Array()
    {
        delete []arr;
        arr = NULL;
        length = 0;
    }

    T& operator[](int index)
    {
        return arr[index];
    }

    int getLength();
};

#endif
