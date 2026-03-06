// Insertion sort follow the below things:
// 1. Its like placing the playing card in a sequence( ascending or descending )
// 5 8 3 4 1
// | |
//   | | ( here first 3 and 8 will swipe and 3 will swipe till its not reach to the place where one before number //		is less than or equal to its own number.)

#include <bits/stdc++.h>

using namespace std;

void selectionSort(int *arr, int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[min_idx] > arr[j])
                min_idx = j;
        }
        swap(arr[i], arr[min_idx]);
    }
}

int main()
{
    int arr[6] = {5, 4, 0, 3, 1, 2};

    selectionSort(arr, sizeof(arr) / sizeof(arr[0]));

    for (int i : arr)
        cout << arr[i] << " ";
}
