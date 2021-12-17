#include<iostream>
#include<utility>
using namespace std;
void swap(int *x, int *y)
{
    int temp = *x;
    *y = *x;
    *x = temp;
}

int partition(int *arr, int s, int e)
{
    int piv = arr[e];
    int i = s;
    int c;
    for(c = s; c < e; c++ )
    {
        if( arr[c] < piv )
        {
            swap(arr[c], arr[i]);
            i++;
        }
    }
    swap(arr[i], arr[c]);
    return i;
}

void QuickSort(int *arr, int s, int e)
{
    if( s < e )
    {
        int pi = partition(arr, s, e);
        QuickSort(arr, s, pi - 1);
        QuickSort(arr, pi+1, e);
    }
}

int main()
{
    int arr[]{4,1,5,2,3,3,1,1,12,31,12,0,2,1};

    int size = sizeof(arr)/sizeof(arr[1]);

    QuickSort(arr, 0, size -1);
    for(int i =0; i< size;i++)
    {
        cout<<arr[i]<<" ";
    }
    return 0;
}