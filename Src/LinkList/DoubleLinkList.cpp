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
			Data *prev;
			Data( void *dat, Data *temp )
			{
				data = dat;
				next = temp;
			}
	}*head;
	
	public:
	LinkList()
	{
		head = NULL;
	};
	
	void push( void *dat )
	{
		Data *newData = new Data( dat, head );
		
		if( head == NULL )
		{
			newData->prev = NULL;
			head = newData;
		}
		else
		{
			head->prev = newData;
			head = newData;
		}
	}
	
	void display()
	{
	}
	
	~LinkList()
	{
		Data *temp = head;
		cout<<"deleting link list: "<<endl;
		string *ss;
		
		while( temp != NULL )
		{
			ss = (string*)temp->data;
			head = head->next;
			cout<<*ss<<" ";
			delete temp;
			temp = head;
		}
	}
	
	void revPrint()
	{
		Data *temp = head;
		while( temp->next != NULL )
		{
			temp = temp->next;
		}
		string *s;
		
		while( temp != NULL )
		{
			s = (string*)temp->data;
			cout<<*s<<" ";
			temp = temp->prev;
		}
	}
	
	void rec_rev(Data *temp)
	{
/*		Data *cur = NULL;
		Data *temp = head;
		
		while( temp != NULL )
		{
			cur = temp;
			temp = temp->next;
			cur->next = cur->prev;
			cur->prev = temp;
		}
		head = cur;*/
		
		Data *cur = temp;
		temp = temp->next;
		cur->next = cur->prev;
		cur->prev = temp;
		
		if( temp != NULL )
			rec_rev( temp );
		else
			head = cur;
	}
	
	void rev()
	{
		rec_rev( head );
	}
};

int main()
{
	LinkList ll;
	string ss;
	ifstream in("k.txt");
	while( getline( in, ss ) )
	{
		ll.push( new string(ss) );
	}
	//ll.revPrint();
	ll.rev();
}