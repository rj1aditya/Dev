#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>



struct A
{
	int a;
	float b;
	//char c;
};


void* func( void *pStrr)
{
	int n = 0;
	struct A *pStr = (struct A*)pStrr;
	while( n<5 )
	{
		
		printf("%d Structure value are: ",n );
		printf("%d %f", pStr->a, pStr->b );
		printf("\n");
		pStr++;
		n++;
		pthread_exit( (void*)500 );
	}
}

int main()
{
	pthread_t td1;
	int x;
	struct A *pStr = (struct A*)malloc(5*sizeof( struct A ));
	struct A *temp = pStr;
	for( int i = 0; i < 5; i++ )
	{
		pStr->a = 1 + i;
		pStr->b = 1.1 + (float)i;
		pStr++;
	}
	// Some importing pointing of sending structure to the thread function.
	// 1. temp pointer structure pass as a add. of allocated memory instead of doing &temp( here it would pass
	// its own add. which wont be nedded there in thread function.
	pthread_create( &td1, NULL, func, temp);
	
	int n = 1000000000;

	while( n>0 )
	{
		n--;
		//printf("win ");
	}
	pthread_join( td1, (void*)&x );
	
	printf("value returned from pthread: %d", x);
}
	