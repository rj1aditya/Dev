#include<iostream>
#include<utility>
using namespace std;

void swap(int *x, int *y)
{
    int temp = *x;
    *y = *x;
    *x = temp;
}

void selectionSort(int *arr, int arrSize)
{
    int min_id = 0;
    for(int i = 0; i < arrSize-1; i++)
    {
        min_id = i;
        for(int j = i+1; j < arrSize; j++)
        {
            if(arr[j] < arr[min_id])
                min_id = j;
        }
        swap(arr[min_id], arr[i]);
    }
}

int main()
{
    int arr[]{4,1,5,2,0,7};

    int size = sizeof(arr)/sizeof(arr[1]);
    selectionSort(arr, size);

    cout<<"Array after selection sort:\n";
	for( int i = 0; i < size; i++ )
		cout<<arr[i]<<" ";

    return 0;
}