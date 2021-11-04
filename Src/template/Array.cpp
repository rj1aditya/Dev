#include"Array.h"


template <typename T>
int Array<T>::getLength()
{
    return length;
}

template class Array<int>; // Explicitly instantiate template Array<int>
template class Array<double>; // Explicitly instantiate template Array<double>