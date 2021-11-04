//fprintf and fscanf are use to read and write a mixed data(int,string,char,float) from a file.

#include<stdio.h>
#include<string.h>

int main()
{	
	struct student
	{
		int roll;
		char name[10];
	};
	
	struct student ravi;
	
	// fp will point to file lun.txt in write mode.
	FILE *fp = fopen( "lun.txt", "a" );

	if( fp != NULL )
		printf("lun.txt file opened successfully in write mode\n");
	else
		printf("Opening failed\n");
	
	//reset a sturct with 0 value
	//returns void*
	memset( &ravi, 0, sizeof( ravi ) );
	
	printf("Enter name of student:");
	scanf("%s",ravi.name);
	
	printf("Enter the roll no of the student:");
	scanf("%d",&ravi.roll);
	
	//fprintf use to write a mixed data in a file
	fprintf(fp, "%d %s", ravi.roll,ravi.name);
	
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
		
	memset( &ravi, 0, sizeof( ravi ) );
	
	//fscnaf are use to read mixed data from a file.
	fscanf(fp, "%d  %s", &ravi.roll,ravi.name);
	
	printf("Name	Roll No\n");
	printf("%s	%d\n",ravi.name,ravi.roll);
	
	x = fclose( fp );
	if( x == 0 )
		printf("\nFile closed successfully\n");
	fp = NULL;
		
	return 0;
}