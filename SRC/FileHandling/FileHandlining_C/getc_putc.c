//getc and putc are use to read and write a character from a file.

#include<stdio.h>

void func( const char *c )
{
	// printf("%c",c);
}

int main()
{	
	// fp will point to file lun.txt in write mode.
	FILE *fp = fopen( "lun.txt", "w" );

	if( fp != NULL )
		printf("lun.txt file opened successfully in write mode\n");
	else
		printf("Opening failed\n");
	
	// var to write a char in a file
	char c;
	
	printf("Start writing in a file, press ctrl+d to stop\n");
	
	//getchar() function is used to get a character from a user.
	while( ( c = getchar() ) != EOF )
	{
		putc( c, fp );
	}

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
		
	while( ( c = getc(fp) ) != EOF )
		printf("%c", c );

	x = fclose( fp );
	if( x == 0 )
		printf("\nFile closed successfully\n");
	fp = NULL;
		
	return 0;
}