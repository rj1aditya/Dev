class Solution
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