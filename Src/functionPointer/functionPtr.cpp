#include<iostream>
using namespace std;

int double_int(int x)
{
    return 2*x;
}

int square_int(int x)
{
    return x*x;
}

void transform(int *arr, int len, int (*ope)(int))
{
    for(auto i = 0; i < len; i++)
    {
        arr[i] = ope(arr[i]);
    }
}

int main()
{
    int arr1[] = {1,2,3,4,5,6,7,8};
    int arr2[] = {1,2,3,4,5,6,7,8};
    transform(arr1, sizeof(arr1)/sizeof(int), &double_int);
    transform(arr2, sizeof(arr2)/sizeof(int), &square_int);

    for(auto i = 0; i < sizeof(arr1)/sizeof(int); i++)
    {
        cout<<arr1[i]<<" "<<arr2[i]<<endl;
    }
}