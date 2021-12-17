#include<bits/stdc++.h>
using namespace std;


void DFS(int G[8][8], int vtx, int n)
{
    static int visited[8] = {0};

    if(visited[vtx] == 0)
    {
        cout<<vtx<<" ";
        visited[vtx] = 1;
        for(int i = 1; i < n; i++ )
        {
            if(visited[i] == 0 && G[vtx][i] == 1)
            {
                DFS(G, i, n);
            }
        }        
    }

}

int main()
{
    int A[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 1, 1, 1, 0, 0, 0},
                   {0, 1, 0, 1, 0, 0, 0, 0},
                   {0, 1, 1, 0, 1, 1, 0, 0},
                   {0, 1, 0, 1, 0, 1, 0, 0},
                   {0, 0, 0, 1, 1, 0, 1, 1},
                   {0, 0, 0, 0, 0, 1, 0, 0},
                   {0, 0, 0, 0, 0, 1, 0, 0}};

    int n = sizeof(A[0])/sizeof(A[0][0]);
    //here 1 is vertex 1
    DFS(A, 1, n);
    return 0;
}