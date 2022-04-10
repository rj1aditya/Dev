#include <stdio.h>
void Insert(int A[], int n)
{
    int i = n, temp;
    temp = A[i];
    while (i > 1 && temp > A[i / 2])
    {
        A[i] = A[i / 2];
        i = i / 2;
    }
    A[i] = temp;
}


// How to create a heap
int main()
{
    int H[] = {0, 40, 70, 80}; // we leave the 0th idx
    int i;
    for (i = 2; i <= 3; i++) // 1st idx is already a heap, from 2nd index we start arranging the heap.
        Insert(H, i);
 
    // for (i = 3; i > 1; i--)
    // {
    //     Delete(H, i);
    // }
    for (i = 1; i <= 3; i++)
        printf("%d ", H[i]);
    printf("\n");
 
    return 0;
}
