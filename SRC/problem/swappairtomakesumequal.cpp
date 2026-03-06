class Solution
{

public:
    int findSwapValues(int A[], int n, int B[], int m)
    {
        int suma = 0;
        int sumb = 0;
        unordered_set<int> s;
        for (int i = 0; i < n; i++)
        {
            suma += A[i];
        }
        for (int j = 0; j < m; j++)
        {
            sumb = sumb + B[j];
        }

        if (suma == sumb)
        {
            for (int j = 0; j < m; j++)
            {
                s.insert(B[j]);
            }
            for (int i = 0; i < n; i++)
            {
                if (s.find(A[i]) != s.end())
                {
                    return 1;
                }
            }
            return -1;
        }

        int diff = abs(suma - sumb);

        if (diff % 2 != 0)
            return -1;

        diff = diff / 2;
        if (suma > sumb)
        {
            for (int j = 0; j < m; j++)
            {
                s.insert(B[j]);
            }
            for (int i = 0; i < n; i++)
            {
                if (s.find(A[i] - diff) != s.end())
                {
                    return 1;
                }
            }
        }
        if (sumb > suma)
        {
            for (int j = 0; j < n; j++)
            {
                s.insert(B[j]);
            }
            for (int i = 0; i < m; i++)
            {
                if (s.find(B[i] - diff) != s.end())
                {
                    return 1;
                }
            }
        }
        return -1;
    }
};

