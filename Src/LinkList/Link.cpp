#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class LinkList
{
	class Data
	{
		public:
		void *data;
		Data *next;
		Data( void*, Data* );
		~Data()
		{
			cout<<*(string*)data;
			delete (string*)data;
		}
	}*head;
	
	public:
	LinkList()
	{
		head = NULL;
	}
	
	void push( void *data )
	{
		Data *newData = new Data( data, head );
		head = newData;
	}
	
	void display()
	{
		Data *temp = head;
		while( temp != NULL )
		{
			string *ss = (string*)(temp->data); 
			cout<< *ss  << " ";
			temp = temp->next;
		}
	}
	~LinkList()
	{
		Data *temp = head;
		cout<<"deleting link list:"<<endl;
		while( head != NULL )
		{
			head = head->next;
			string *ss = (string*)(temp->data);
			cout<<*ss<< " ";
			delete temp;
			temp = head;
		}
	}
	void rec_rev()
	{
		Data* prev = NULL;
		Data* temp = head;
		rev( head -> next );
	}
	
	void rev( Data* temp)
	{
		( temp->next != NULL )
			rev( temp->next, temp );
		
		if( temp->next == NULL )
			head = temp;
		temp->next = prev;
	}
};

LinkList::Data::Data( void *dat, Data *nxt )
{
	data = dat;
	next = nxt;
}

int main()
{
	LinkList ll;
	ifstream in("L.cpp");
	string s;
	while( getline( in, s ) ){
	
	ll.push( new string(s) );
	}
	cout<<"before reversing a link list"<<endl;
	ll.display();
	cout<<endl;
	
	ll.rec_rev();
	cout<<"after reversing a link list"<<endl;
	ll.display();
	cout<<endl;
}