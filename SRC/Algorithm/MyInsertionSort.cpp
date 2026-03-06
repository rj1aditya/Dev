// Insertion sort follow the below things:
// 1. Its like placing the playing card in a sequence( ascending or descending )
// 5 8 3 4 1
// | |
//   | | ( here first 3 and 8 will swipe and 3 will swipe till its not reach to the place where one before number //		is less than or equal to its own number.)


#include<iostream>
using namespace std;

void InsertionSort( int *arr, int size )
{
 	for( int i = 0; i < size - 1 ; ++i )
	{
		for( int j = i + 1; j > 0 && (arr[j] < arr[j-1]); --j )
		{
				arr[j] ^= arr[j-1];
				arr[j-1] ^= arr[j];
				arr[j] ^= arr[j-1];
		}
	}
}

int main()
{
	int arr[6] = { 5, 4, 0, 3, 1, 2};
	
	InsertionSort( arr, sizeof(arr)/sizeof(arr[0]) );
	
	for( int i: arr )
		cout<<arr[i]<<" ";
}

//It worked fine

// Min time complexity: O(n) when array is already sorted e.g. 0 1 2 3 4 5
// Max time complexity: O(n^2) when array is totally unsorted e.g. 5 4 3 2 1 0
// Sortable sort: yes
// Sorting inplace: yes
