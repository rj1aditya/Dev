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
		Data(void *dat, Data *temp)
		{
			data = dat;
			next = temp;
		}
	}*head;
	public:
	LinkList()
	{
		head = NULL;
	}
	
	void push( void *dat )
	{
		Data *newData = new Data(dat,head);
		head = newData;
	}
	
	void display()
	{
	}
	
	~LinkList()
	{
		Data *temp = head;
		cout<<"deleting link list: ";
		
		while( head != NULL )
		{
			head = temp->next;
			string *ss = (string*)temp->data;
			cout<<*ss<<endl;
			delete temp;
			temp = head;
		}
	}
	void rev()
	{
		Data *cur = head;
		Data *prev = NULL;
		Data *nxt = cur->next;
		
		while( nxt != NULL )
		{
			nxt = cur->next;
			cur->next = prev;
			prev = cur;
			cur = nxt;
		}
		head = prev;
	}
};


int main()
{
	LinkList ll;
	ifstream in("k.txt");
	string ss;
	while( getline( in, ss ) )
	{
		ll.push( new string(ss) );
	}
	//ll.rev();
}

