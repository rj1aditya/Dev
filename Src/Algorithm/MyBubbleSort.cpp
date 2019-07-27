// Bubble sort follow the below things:
// 1. As name suggested we make bubble of 2 element.
// 2. and Move in each iteration till last.
// 3. 5 3 2 1 0
// 5 and 3 will swap, 3 5 2 1 0 then 5 and 2 will swap, 3 2 5 1 0 like so on..
// in first largest value will reach to the last, now have to sort only starting 4 then 3, 2, 1, 0


#include<iostream>
using namespace std;

void BubbleSort( int *arr, int size )
{
	// this flag is introduce in the internal loop to check.
	// 1. if no change in the internal loop that indicate all array is sortedm so no need to sorting u can break the outer for
	// loop.
	int flag;
	
 	for( int i = 0; i < size - 1; i++ )
	{
		flag = 0;
		for( int j = 0; j < size-i-1; j++ )
		{
			if( arr[j+1] < arr[j] )
			{
				arr[j+1] ^= arr[j];
				arr[j] ^= arr[j+1];
				arr[j+1] ^= arr[j];			
				flag = 1;
			}
		}
		if( flag != 1 )
			break;
	}
}

int main()
{
	int arr[5] = { 5, 4, 0, 3,1};
	
	BubbleSort( arr, sizeof(arr)/sizeof(arr[0]) );
	
	for( int i = 0; i < 5; i++ )
		cout<<arr[i]<<" ";
}

//It worked fine

// Time complexity : (n-1) + (n-2) + (n-3).....
						n(n-1)/2
						= n^2;