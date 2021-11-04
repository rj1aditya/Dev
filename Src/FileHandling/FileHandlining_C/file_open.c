/*
There are many modes for opening a file:

r - open a file in read mode
w - opens or create a text file in write mode
a - opens a file in append mode
r+ - opens a file in both read and write mode
a+ - opens a file in both read and write mode
w+ - opens a file in both read and write mode
*/

#include<stdio.h>

void func( const char *c )
{
	// printf("%c",c);
}

int main()
{
	//just declaring a variable
	//it will initiate with NULL value.
	FILE *fp1;
	if( fp1 == NULL )
		printf("Null pointer\n");
	else
		printf("Wild pointer\n");
	// O/P: Wild pointer
	
	// fp will point to file lun.txt.
	FILE *fp = fopen( "lun.txt", "w" );	
	int x = fclose( fp ); // 0 return value is success
	printf("%d\n",x);
	//Now fp is become wild pointer.
	if( fp == NULL )
		printf("Null pointer\n");
	else
		printf("Wild pointer\n");
	// O/P: Wild Pointer

	int f = fclose(fp);
	printf("%d\n",f);
	//fclose(fp);// will not cause segmentation fault.
	return 0;
}