#include<iostream>
#include<utility>
using namespace std;
//https://www.youtube.com/watch?v=mB5HXBb_HY8 time complexity explanation
void mergeIt(int *arr, int l, int m, int r)
{
    int leftArraySize = m - l + 1;
    int rightArraySize = r - m;

    int leftArray[leftArraySize];
    int rightArray[rightArraySize];

    for(int i = 0; i < leftArraySize; i++ )
    {
        leftArray[i] = arr[l+i];
    }

    for(int i = 0; i < rightArraySize; i++ )
    {
        rightArray[i] = arr[m+1+i];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while( i < leftArraySize && j < rightArraySize )
    {
        if( leftArray[i] > rightArray[j] )
        {
            arr[k] = rightArray[j];
            j++;
        }
        else
        {
            arr[k] = leftArray[i];
            i++;
        }
        k++;
    }

    while( i < leftArraySize )
    {
        arr[k] = leftArray[i];
        i++;
        k++;
    }
    while( j < rightArraySize )
    {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void breakIt(int *arr, int l, int r)
{
    if(l == r)
        return;
    int m = l + (r-l)/2;

    breakIt(arr, l, m);
    breakIt(arr, m+1, r);
    mergeIt(arr, l, m, r);
}

void mergeSort(int *arr, int l, int r)
{
    breakIt(arr, l, r);
}

int main()
{
    int arr[]{4,1,5,2,3,3,1,1,12,31,12,0,2,1};

    int size = sizeof(arr)/sizeof(arr[1]);

    mergeSort(arr, 0, size -1);
    for(int i =0; i< size;i++)
    {
        cout<<arr[i]<<" ";
    }
    return 0;
}