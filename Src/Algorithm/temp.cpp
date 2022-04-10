#include <bits/stdc++.h>
using namespace std;
class Solution
{

    long long inversionC = 0;
    void mergeIt(long long  *arr, long long l, long long m, long long r)
    {
        long long  leftArraySize = m - l + 1;
        long long  rightArraySize = r - m;

        long long  leftArray[leftArraySize];
        long long  rightArray[rightArraySize];

        for (long long i = 0; i < leftArraySize; i++)
        {
            leftArray[i] = arr[l + i];
        }

        for (long long i = 0; i < rightArraySize; i++)
        {
            rightArray[i] = arr[m + 1 + i];
        }

        long long i = 0;
        long long j = 0;
        long long k = l;

        while (i < leftArraySize && j < rightArraySize)
        {
            if(leftArray[i] <= rightArray[j])
            {
                arr[k] = leftArray[i];
                i++;
                k++;
            }
            else if(leftArray[i] >= rightArray[j])
            {
                arr[k] = rightArray[j];
                inversionC += leftArraySize - i;
                j++;
                k++;
            }
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

    void breakIt(long long  *arr, long long l, long long r)
    {
        if (l == r)
            return;
        long long m = l + (r - l) / 2;

        breakIt(arr, l, m);
        breakIt(arr, m + 1, r);
        mergeIt(arr, l, m, r);
    }

public:
    // arr[]: Input Array
    // N : Size of the Array arr[]
    // Function to count inversions in the array.
    long long int inversionCount(long long  *arr, long long N)
    {
        // Your Code Here
        long long  arrbkup[N];
        for (long long  i = 0; i < N; i++)
            arrbkup[i] = arr[i];

        breakIt(arrbkup, 0, N - 1);

        return inversionC;
    }
};
int main()
{
    Solution s;
    long long  arr[] = {5,3,2,4,1};
    cout << s.inversionCount(arr, 5);
    return 0;
}