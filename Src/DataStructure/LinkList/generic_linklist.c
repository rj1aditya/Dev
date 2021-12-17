#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node
{
	void *data;
	struct Node *next;
};

struct Node *head = NULL;

struct Node* insert( void *ptr )
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	
	temp->next = NULL;
	temp->data = ptr;
	
	if( head == NULL )
		head = temp;
	else
	{
		temp->next = head;
		head = temp;
	}
	//printf("%s",(char*)ptr);
}

void display()
{
	struct Node *temp = head;
	while( temp != NULL )
	{
		printf("%s -> ",(char*)temp->data);
		temp = temp->next;
	}
	printf("NULL");
}

void search( void *ptr )
{
	//printf("%s",(char*)ptr);
	struct Node* temp = head;
	while( temp != NULL )
	{
		if( !strcmp( (char*)ptr, (char*)temp->data ) )
		{
			printf("\nElement is present in the link list\nNode value is: %s", (char*)temp->data);
			return;
		}
		temp = temp->next;
	}
	if( temp == NULL )
		printf("Element is not present in the link list\n");
}

int main()
{
	int choice;
	void *temp;
	do
	{
		printf("Select below mentioned operation:\n");
		printf("1. Insert\n");
		printf("2. Search\n");
		printf("3. delete\n");
		printf("4. display\n");
		
		scanf("%d",&choice);
		switch( choice )
		{
			case 1:
				temp = (char*)malloc(sizeof(char)*10);
				printf("Enter a value:");
				scanf("%s",(char*)temp);
				head = insert(temp);
				break;
			case 2:
				printf("Enter a string to be search in a link list:");
				char arr[10];
				scanf("%s",arr);
				search( arr );
				break;
			case 4:
				display();
				break;
		}
	}while( choice != 0 );
}
