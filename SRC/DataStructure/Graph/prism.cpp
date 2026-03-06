#include <iostream>
#include <stdio.h>
using namespace std;
#define V 8
#define I INT32_MAX

void PrimsMST(int G[V][V], int vertix)
{
    int t[2][vertix - 2];
    int near[vertix + 1];
    for (int x = 0; x < vertix + 1; x++)
    {
        near[x] = I;
    }
    cout << endl;
    int min = INT32_MAX;
    int u = 0, v = 0;
    int k;
    //to get the min u and v edge
    for (int i = 1; i <= vertix; i++)
    {
        for (int j = i; j <= vertix; j++)
        {
            if (G[i][j] < min)
            {
                u = i;
                v = j;
                min = G[i][j];
            }
        }
    }
    printf("\nInitial Edge [%d,%d] with weight: [%d]", u, v, G[u][v]);

    near[u] = 0;
    near[v] = 0;
    t[0][0] = u;
    t[1][0] = v;

    for (int k = 1; k <= vertix; k++)
    {
        if (near[k] == 0)
            continue;

        if (G[k][u] < G[k][v])
            near[k] = u;
        else
            near[k] = v;
    }

    for (int i = 1; i <= sizeof(t[0]) / sizeof(t[0][0]); i++)
    {
        int min1 = I;
        int p1, p2;
        for (int k = 1; k <= vertix; k++)
        {
            if (near[k] != 0 && G[k][near[k]] < min1)
            {
                min1 = G[k][near[k]];
                p1 = k;
            }
        }

        t[0][i] = p1;
        t[1][i] = near[p1];
        near[p1] = 0;

        for(int j = 1; j <= vertix; j++)
        {
            if (near[j] != 0 && G[j][p1] < G[j][near[j]])
                near[j] = p1;
        }

    }

    for (int i = 0; i <= sizeof(t[0]) / sizeof(t[0][0]); i++)
    {
        cout << t[0][i] << "," << t[1][i] << endl;
    }
}

int main()
{
    int cost[V][V]{
        {I, I, I, I, I, I, I, I},
        {I, I, 25, I, I, I, 5, I},
        {I, 25, I, 12, I, I, I, 10},
        {I, I, 12, I, 8, I, I, I},
        {I, I, I, 8, I, 16, I, 14},
        {I, I, I, I, 16, I, 20, 18},
        {I, 5, I, I, I, 20, I, I},
        {I, I, 10, I, 14, 18, I, I},
    };

    int n = sizeof(cost[0]) / sizeof(cost[0][0]) - 1;
    printf("\nSizeo of cost array is[%d]", n);
    PrimsMST(cost, n);
    return 0;
}