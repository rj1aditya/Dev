//fread and fwrite are use to read and write a stream of data from a file.

#include<stdio.h>
#include<string.h>

int main()
{	

	// fp will point to file lun.txt in write/read mode.
	FILE *fp = fopen( "lun.txt", "rb+" );

	if( fp != NULL )
		printf("lun.txt file opened successfully in write mode\n");
	else
		printf("Opening failed\n");

	char stream[2][100] = {"O Mahi ve is one of my favorite song from Kesari movie :) \n","O Mahi ve is one of my favorite song from Kesari movie :) \n"};
	
	char read_stream[2][100];
	
	memset( read_stream, 0, sizeof(read_stream));
	//fwrite can write a number of stream in a file.
	
	
	fwrite(stream, sizeof(stream), 2, fp);

	rewind(fp);
	
	
	//fread are use to read number of stream from a file.
	fread(read_stream, sizeof(stream),2,fp);
	for( int i = 0; i < 2; i++)
	{
		printf("%s\n",read_stream[i]);
	}
	
	int x = fclose( fp );
	if( x == 0 )
		printf("\nFile closed successfully\n");
	fp = NULL;

	
	return 0;
}