#include <iostream>
#include <utility>
using namespace std;

void CountingSort(int *arr, int size, int max)
{
    int *countArr = (int *)malloc(sizeof(int) * (max + 1));
    for (int i = 0; i <= max; i++)
        countArr[i] = 0;

    for (int i = 0; i < size; i++)
    {
        countArr[arr[i]] = countArr[arr[i]] + 1;
    }

    for (int i = 0; i <= max; i++)
    {
        while (countArr[i] > 0)
        {
            countArr[i]--;
            cout << i << " ";
        }
    }

    free(countArr);
}

int main()
{
    int arr[]{4, 1, 5, 2, 0, 7, 1, 5};

    int size = sizeof(arr) / sizeof(arr[1]);
    int max = 0;
    for (int i = 0; i < size; i++)
    {
        if (max < arr[i])
            max = arr[i];
    }
    CountingSort(arr, size, max);
    return 0;
}