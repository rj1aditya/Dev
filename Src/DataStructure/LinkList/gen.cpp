#include<iostream>
using namespace std;

class LinkList
{
	class Node
	{
		public:
		void *data;
		Node *next;
		Node( Node *temp, void *dat )
		{
			data = dat;
			next = temp;
		}
		~Node()
		{
			delete (char*)data;
		}
	}*head;
	
	public:
	LinkList()
	{
		head = NULL;
	}
	
	~LinkList()
	{
		cout<<"LinkList Deleted"<<endl;
	}
	
	void insert()
	{
		char *c = new char[10];
		cin>>c;
		Node *temp = new Node( head, c );
		head = temp;
	}
	
	void display()
	{
		Node *temp = head;
		while( temp != NULL )
		{
			cout<<(char*)temp->data<<"->";
			temp = temp->next;
		}
		cout<<"NULL"<<endl;
	}
	
	void Delete()
	{
		Node *temp = head;
		
		while( head != NULL )
		{
				head = head->next;
				delete temp;
				temp = head;
		}
	}
	
	void action()
	{
	  int option = 0;
	  while( option != -1 )
	  {
		cout<<"Select below operation"<<endl;
		cout<<"1. Insert"<<endl;
		cout<<"2. Display"<<endl;
		cout<<"3. Delete"<<endl;
		cout<<"-1. Exit"<<endl;
		cin>>option;
		
		switch( option )
		{
			case 1:
			insert();
			break;
			case 2:
			display();
			break;
			case 3:
			Delete();
			break;
		}
	  }
	}		
};

int main()
{
	LinkList ll;
	ll.action();
}