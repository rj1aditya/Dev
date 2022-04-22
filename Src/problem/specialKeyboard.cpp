#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    long long int optimalKeys(int N)
    {
        // code here
        if (N <= 6)
            return N;

        int screen[N]{0};
        for (int i = 0; i < 6; i++)
        {
            screen[i] = i + 1; // 1 2 3 4 5 6
        }

        for (int i = 6; i < N; i++)
        {
            for (int b = i - 3; b >= 0; b--)
            {
                int curr = screen[b] * (i - b - 1);

                screen[i] = max(screen[i], curr);
            }
        }

        return screen[N - 1];
    }
};

// A recursive function that returns the optimal length string
// for N keystrokes
int findoptimal(int N)
{
    // The optimal string length is N when N is smaller than 7
    if (N <= 6)
        return N;

    // Initialize result
    int max = 0;

    // TRY ALL POSSIBLE BREAK-POINTS
    // For any keystroke N, we need to loop from N-3 keystrokes
    // back to 1 keystroke to find a breakpoint 'b' after which we
    // will have Ctrl-A, Ctrl-C and then only Ctrl-V all the way.
    int b;
    for (b = N - 3; b >= 1; b--)
    {

        // If the breakpoint is s at b'th keystroke then
        // the optimal string would have length
        // (n-b-1)*screen[b-1];
        int curr = (N - b - 1) * findoptimal(b);
        if (curr > max)
            max = curr;
    }
    return max;
}