#include <iostream>
#include <utility>
using namespace std;
// https://www.youtube.com/watch?v=mB5HXBb_HY8 time complexity explanation
void mergeIt(int *arr, int l, int m, int r)
{
    int leftArraySize = m - l + 1;
    int rightArraySize = r - m;

    int leftArray[leftArraySize];
    int rightArray[rightArraySize];

    for (int i = 0; i < leftArraySize; i++)
    {
        leftArray[i] = arr[l + i];
    }

    for (int i = 0; i < rightArraySize; i++)
    {
        rightArray[i] = arr[m + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < leftArraySize && j < rightArraySize)
    {
        if (leftArray[i] > rightArray[j])
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

    while (i < leftArraySize)
    {
        arr[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < rightArraySize)
    {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}

void breakIt(int *arr, int l, int r)
{
    if (l == r)
        return;
    int m = l + (r - l) / 2;

    breakIt(arr, l, m);
    breakIt(arr, m + 1, r);
    mergeIt(arr, l, m, r);
}

void mergeSort(int *arr, int l, int r)
{
    breakIt(arr, l, r);
}
class SS
{
    long long ans = 0;
    // arr[]: Input Array
    // N : Size of the Array arr[]
    // Function to count inversions in the array.
    void merge(long long arr[], long long left, long long mid, long long right)
    {
        long long n = mid - left + 1;
        long long m = right - mid;
        long long a[n], b[m];
        for (int i = 0; i < n; i++)
        {
            a[i] = arr[i + left];
        }
        for (int i = 0; i < m; i++)
        {
            b[i] = arr[i + mid + 1];
        }

        long long i = 0, j = 0, k = left;
        while (i < n and j < m)
        {
            if (a[i] <= b[j])
            {
                arr[k] = a[i];
                k++;
                i++;
            }
            else if (a[i] >= b[j])
            {
                arr[k] = b[j];
                j++;
                k++;
                ans += n - i;
            }
        }
        while (i < n)
        {
            arr[k] = a[i];
            k++;
            i++;
        }
        while (j < m)
        {
            arr[k] = b[j];
            j++;
            k++;
        }
    }
    void cnt(long long arr[], long long left, long long right)
    {

        if (left < right)
        {
            long long mid = left + (right - left) / 2;
            cnt(arr, left, mid);
            cnt(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    public:
    long long int inversionCount(long long arr[], long long N)
    {
        // Your Code Here
        cnt(arr, 0, N - 1);
        return ans;
    }
};


int main()
{
    int arr[]{4, 1, 5, 2, 3, 3, 1, 1, 12, 31, 12, 0, 2, 1};

    int size = sizeof(arr) / sizeof(arr[1]);

    mergeSort(arr, 0, size - 1);
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}