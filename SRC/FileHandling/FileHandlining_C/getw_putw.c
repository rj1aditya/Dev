//getw and putw are use to read and write a int from a file.

#include<stdio.h>


int main()
{	
	// fp will point to file lun.txt in write mode.
	FILE *fp = fopen( "lan.txt", "w" );

	if( fp != NULL )
		printf("lun.txt file opened successfully in write mode\n");
	else
		printf("Opening failed\n");
	int var;
	for( int p = 0; p < 10; p++ )
	{
		//putw function stored int data in binary format in a file.
		scanf("%d",&var);
		putw( var, fp );
	}

	int x = fclose( fp );
	if( x == 0 )
		printf("\nFile closed successfully\n");
	fp = NULL;
	
	//open a file in read mode
	fp = fopen( "lan.txt", "r" );

	if( fp != NULL )
		printf("lun.txt file opened successfully in read mode\n");
	else
		printf("Opening failed\n");
		
	int i;
	while( ( i = getw(fp) ) != EOF )
		printf("%d\n", i );

	x = fclose( fp );
	if( x == 0 )
		printf("\nFile closed successfully\n");
	fp = NULL;
		
	return 0;
}