//fgets and fputs are use to read and write a string from a file.

#include<stdio.h>
#include<string.h>

int main()
{	
	// fp will point to file lun.txt in write mode.
	FILE *fp = fopen( "lun.txt", "a" );

	if( fp != NULL )
		printf("lun.txt file opened successfully in write mode\n");
	else
		printf("Opening failed\n");
	
	// char array of size 10 to write a string in a file
	char str[50];
	
	//reset a string with 0 value
	//returns void*
	memset( str, 0, sizeof( str ) );
	
	memcpy( str, "Chupke chupke song is playing right now", sizeof(str) );
	
	//fputs use to write a string in a file
	fputs( str, fp );
	
	int x = fclose( fp );
	if( x == 0 )
		printf("\nFile closed successfully\n");
	fp = NULL;
	
	//open a file in read mode
	fp = fopen( "lun.txt", "r" );

	if( fp != NULL )
		printf("lun.txt file opened successfully in read mode\n");
	else
		printf("Opening failed\n");
		
	memset( str, 0, sizeof( str ) );
	
	fgets( str, sizeof(str), fp );
		printf("string read from the file is:\n");
		printf("%s",str);
	x = fclose( fp );
	if( x == 0 )
		printf("\nFile closed successfully\n");
	fp = NULL;
		
	return 0;
}