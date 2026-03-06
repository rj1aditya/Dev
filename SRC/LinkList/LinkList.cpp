#include"/home/aditya/Dev/App/Src/LinkList/LinkList.h"

bool PalindromeFlag = 1;
Data* init;

Data::Data()
{
	next = NULL;
}

LinkList::LinkList()
{
	head = NULL;
}
LinkList::~LinkList()
{
	DeleteLinkList();
}
void LinkList::InsertElement()
{
	Data *newData = new Data;
	cout<<"Enter value of LunNo: ";
	cin>>newData->LunNo;

	if( head == NULL )
		head = newData;
	else
	{
		Data *temp = head;
		while( temp->next != NULL )
			temp = temp->next;

		temp->next = newData;
	}
}

void LinkList::DeleteLinkList()
{
	Data *temp = head;
	cout<<endl<<"Deleting link list in sequence: ";
	while( temp != NULL )
	{
		cout<< temp -> LunNo << " ";
		head = temp -> next;
		delete temp;
		temp = head;
	}
	cout<<endl;
}

void LinkList::Display()
{
	Data *temp = head;
	while( temp != NULL)
	{
		cout<<temp->LunNo<<" ";
		temp = temp->next;
	}
	cout<<endl;
}

void LinkList::DeleteNode()
{
	int NodeValue;
	cout<<"Enter value of node to be deleted: ";
	cin>> NodeValue;

	Data *cur = head;
	Data *prev;
	
	if( cur->LunNo == NodeValue )
	{
		head = head->next;
		delete cur;
		return;
	}
	
	prev = cur;
	cur = cur->next;

		while( cur != NULL )
		{
			if( cur->LunNo == NodeValue )
			{
				prev->next = cur->next;
				delete cur;
				break;
			}
			prev = cur;
			cur = cur->next;
		}
		if( cur == NULL )
			cout<<"element is not present in the link list"<<endl;	
	
	/*while( cur->LunNo != NodeValue )
	{
		prev = cur;
		cur = cur->next;
	}
	
	if( cur == head )
	{
		head = head->next;
		delete cur;
	}
	else
	{
		//ptr = cur;
		prev->next = cur->next;
		delete cur;
	}*/
	
}

void LinkList::DeleteNodeAtGivenLoc()
{
	int op;
	cout<<" Enter specific posiotion in link list node to be deleted: ";
	cin >> op ;
	Data *cur = head;
	Data *prev = NULL;
	
	/*for( int i = 1; i < op && cur != NULL ; i++ )
	{
		prev = cur;
		cur = cur->next;
	}
	if( cur == NULL )
	{
		cout<<"Error: Given node position in out of LinkList range";
		return;
	}
	if( prev == NULL )
	{
		Data *temp = cur;
		cur = cur->next;
		head = cur;
		delete temp;
	}
	else
	{
		Data *temp = cur;
		cur = cur->next;
		prev->next = cur;
		delete temp;
	}*/
	
	if( op == 1 )
	{
		head = head->next;
		delete cur;
	}
	
	for( int i = 2; cur != NULL; i++ )
	{
		
		prev = cur;
		cur = cur->next;
		
		if( i == op )
		{
			prev->next = cur->next;
			delete cur;
			break;
		}
	}
}

int LinkList::getLength(Data *temp)
{
	if( temp != NULL )
	{
		return 1 + getLength(temp->next);
	}
	else
		return 0;
}

int LinkList::Length()
{
	return  getLength(head);
}

bool LinkList::IsPresent(Data *temp,int key)
{
	if( temp != NULL && temp->LunNo != key )
		IsPresent(temp->next, key );
	else if( temp == NULL )
		return false;
	else
		return true;	
}

bool LinkList::SearchElement()
{
	int key;
	cout<<"Enter node value to be search: ";
	cin>>key;

	return IsPresent(head,key);
}

void LinkList::FromEnd(Data *temp, int n)
{
	static int i = 0;
	if( temp != NULL )
	{
		i = 0;
		FromEnd( temp->next, n );
	}
	if( i++ == n )
	{
		cout<< n <<"th element from end is: "<< temp->LunNo;
	}
}

void LinkList::NthNodeFromEnd()
{
	int n;
	int element;
	cout<<"Enter location no to be search from the end: ";
	cin>> n;
	FromEnd(head,n);
}

Data* LinkList::MiddleElement()
{
	Data *fast_ptr = head;
	Data *slow_ptr = head;

	if( head != NULL )
	{
		while( fast_ptr != NULL && fast_ptr->next != NULL )
		{
			fast_ptr = fast_ptr->next->next;
			slow_ptr = slow_ptr->next;
		}
	}
	else
		return head;
	cout<<"Middle node is: "<< slow_ptr->LunNo<<endl;
	return slow_ptr;
}

int LinkList::Occurance(Data *temp, int val)
{
	if( temp != NULL && temp->LunNo == val )
	{
		return 1 + Occurance( temp->next, val );
	}
	else if( temp != NULL )
		Occurance(temp->next,val);
	else
		return 0;
}

void LinkList::NoofOccurance()
{
	int val;
	cout<<"Enter an element to find the no of occurance in link list: ";
	cin>> val;
	int count = Occurance(head,val);
	cout<<"No of occurance of "<< val <<"node is: "<< count<<endl;
}

void LinkList::FindLengthOfLoop(Data *temp)
{
	Data *ptr1 = temp;
	int count = 1;

	while( ptr1->next != temp )
	{
		count++;
		ptr1 = ptr1->next;
	}

	cout<<"Loop detected which length is: "<< count << endl;
}

void LinkList::FindLoop()
{
	//this line of code is just to make looped link list ..//
	Data *temp = head;
	Data *temp1 = head;

	while( temp->next != NULL )
		temp = temp->next;

	temp->next = temp1->next->next;
	// looped link list ended
	
	Data *fast = head;
	Data *slow = head;
	while( fast != NULL && fast->next != NULL )
	{
		fast = fast->next->next;
		slow = slow->next;
		if( fast == slow )
		{
	//removing loop from link list
			FindLengthOfLoop(fast);
			temp->next = NULL;
			return;
	//end
		}
	}
	if( fast == NULL || fast->next == NULL )
		cout<<"Loop not detected"<<endl;
}


void LinkList::IsPalindrome(Data *temp)
{
/*
	Data *mid = MiddleElement();
	
	if( Length() % 2 != 0 )
	{
		Data *mid_ptr = mid->next;
		Data *cur_ptr = mid_ptr;
		Data *prev_ptr;
		Data *next_ptr = cur_ptr->next;

		while( next_ptr != NULL )
		{
			prev_ptr = cur_ptr;
			cur_ptr = next_ptr;
			next_ptr = next_ptr->next;

			cur_ptr->next = prev_ptr;
		}
		mid_ptr->next = NULL;
		mid_ptr = cur_ptr;
		mid->next = mid_ptr;

		Data *p1 = head;
		Data *p2 = mid_ptr;
		while( p1->next != mid_ptr )
		{
			if( p1->LunNo == p2->LunNo )
			{
				p1 = p1->next;
				p2 = p2->next;
				continue;
			}
			else
			{
				cout<<"Not Palindrome"<<endl;
				break;
			}
		}
		if( p1 -> next == mid_ptr )
			cout<<"Palindrome"<<endl;
	}
	else
	{
		Data *mid_bfr = head;
		while( mid_bfr -> next != mid )
			mid_bfr = mid_bfr->next;

		//Data *mid_ptr = mid;
		Data *cur_ptr = mid;
		Data *prev_ptr;
		Data *next_ptr = cur_ptr->next;

		while( next_ptr != NULL )
		{
			prev_ptr = cur_ptr;
			cur_ptr = next_ptr;
			next_ptr = next_ptr->next;

			cur_ptr->next = prev_ptr;
		}
		mid->next = NULL;
		mid = cur_ptr;
		mid_bfr->next = mid;

		Data *p1 = head;
		Data *p2 = mid;
		while( p1 != mid )
		{
			if( p1->LunNo == p2->LunNo )
			{
				p1 = p1->next;
				p2 = p2->next;
				continue;
			}
			else
			{
				cout<<"Not Palindrome"<<endl;
				break;
			}
		}
		if( p1 == mid )
			cout<<"Palindrome"<<endl;


	}
*/
	if( temp->next != NULL )
		IsPalindrome( temp->next );
	
	FindPalindrome( temp );

}

void LinkList::FindPalindrome( Data *temp )
{

	if( init->LunNo == temp->LunNo && PalindromeFlag == 1 )
	{
		init = init->next;
		PalindromeFlag = 1;
	}
	else
		PalindromeFlag = 0;
}

void LinkList::Reverse()
{
	Data *cur_ptr = head;
	Data *prev_ptr;
	Data *next_ptr = cur_ptr->next;

	while( next_ptr != NULL )
	{
		prev_ptr = cur_ptr;
		cur_ptr = next_ptr;
		next_ptr = next_ptr->next;

		cur_ptr->next = prev_ptr;
	}
	head->next = NULL;
	head = cur_ptr;
}

void LinkList::RemoveDuplicatesFromSortedLL()
{
	Data *ptr = head;
	while( ptr != NULL && ptr -> next != NULL )
	{
		//in case if I do not set condition ptr != NULL in above while loop then
		// if link list would be like 1->2->3->4->5->5->null
		// in this case lower while loop would make ptr = null ( check point 1 )
		// and in above while loop when it would go to check ptr->next != NULL segmentation 
		// fault would come...
		while( ptr->next != NULL && ptr->LunNo == ptr->next->LunNo )
		{
			Data *temp = ptr->next;
			ptr -> next = ptr->next->next;
			delete temp;
			temp = ptr->next;
		}
		ptr = ptr->next; // check point 1
	}
}

void LinkList::RemoveDuplicatesFromUnsortedLL()
{
	Data *ptr = head;
	while( ptr != NULL && ptr->next != NULL )
	{
		Data *temp = ptr->next;
		Data *temp_prev = ptr;
		while( temp != NULL )
		{
			if( temp->LunNo == ptr->LunNo )
			{
				temp_prev->next = temp->next;
				delete temp;
				temp = ptr->next;
			}
			else
			{
				temp_prev = temp;
				temp = temp->next;
			}
		}
		ptr = ptr->next;
	}
}

void LinkList::SwappingNode()
{
	int x;
	int y;
	cout<<"Enter any 2 nodes to be swapped: "<<endl;
	cin>>x>>y;
	
	Data *fn1 = head;
	Data *fn2 = head->next;
	Data *fn1_prev = NULL ;
	Data *fn2_prev = NULL ;
	while( fn1 != NULL || fn2->next != NULL )
	{
		if( fn1 -> LunNo != x )
		{
			fn1_prev = fn1;
			fn1 = fn1->next;
		}
		if( fn2 -> LunNo != y )
		{
			fn2_prev = fn2;
			fn2 = fn2->next;
		}
		if(fn1 -> LunNo == x && fn2 -> LunNo  == y)
		{
			break;
		}
	}

	Data *temp;
	if( fn1_prev != NULL )
		fn1_prev->next = fn2;
	else
		head = fn2;
	if( fn2_prev != NULL )
		fn2_prev->next = fn1;
	else
		head = fn1;

	temp = fn1->next;
	fn1->next = fn2->next;
	fn2->next = temp;


/*
	cout<<"value of fn1 is: "<<fn1->LunNo<<endl;
	cout<<"value of fn2 is: "<<fn2->LunNo<<endl;	
	cout<<"value of fn1_prev is: "<<fn1_prev->LunNo<<endl;
	cout<<"value of fn2_prev is: "<<fn2_prev->LunNo<<endl;	
*/
}


void LinkList::start()
{
	int op = 1;
	while( op )
	{
		cout<< "Select operation mentioned below: "<<endl;
		cout<< "1. Insert"<<endl;
		cout<< "2. Display"<<endl;
		cout<< "3. Delete all link list"<<endl;
		cout<< "4. Delete a node"<<endl;
		cout<< "5. Delete a node at specific location"<<endl;
		cout<< "6. Find length"<<endl;
		cout<< "7. Search element"<<endl;
		cout<< "8. Nth element from last"<<endl;
		cout<< "9. Find Middle element/Node"<<endl;
		cout<< "10. Find the no of occurance of given element"<<endl;
		cout<< "11. Find loop"<<endl;
		cout<< "12. Find palindrome"<<endl;
		cout<< "13. Reverse LinkList"<<endl;
		cout<< "14. Remove Duplicates from sorted link list"<<endl;
		cout<< "15. Remove Duplicated from unsorted link list"<<endl;
		cout<< "16. Swapping node"<<endl;
		cout<< "0. Exit"<<endl;
		cin>>op;

		switch( op )
		{
			case 1:
				InsertElement();
				break;
			case 2:
				Display();
				break;
			case 3:
				DeleteLinkList();
				break;
			case 4:
				DeleteNode();
				cout<<"After deletion of node: ";
			       	Display();
				break;
			case 5:
				DeleteNodeAtGivenLoc();
				cout<<"After deletion of node: ";
			       	Display();
				break;
			case 6:
				cout<<"Length of link list is: ";
				cout<<Length();
				break;
			case 7:
				bool x;
				x = SearchElement();
				if( x )
					cout<<"Present"<<endl;
				else
					cout<<"Not Present"<<endl;
				break;
			case 8:
				NthNodeFromEnd();
				break;
			case 9:
				Data *mid;
			        mid = MiddleElement();
				break;
			case 10:
				NoofOccurance();
				break;
			case 11:
				FindLoop();
				break;
			case 12:
				PalindromeFlag = 1;
			        init = head;	
				IsPalindrome(head);
				
				if ( PalindromeFlag )
					cout<<"Palindrome"<<endl;
				else
					cout<<"Not Palindrome"<<endl;
				break;
			case 13:
				Reverse();
				cout<<"After reversing Link List become: ";
				Display();
			case 14:
				RemoveDuplicatesFromSortedLL();
				break;
			case 15:
				RemoveDuplicatesFromUnsortedLL();
				break;
			case 16:
				SwappingNode();
				break;
			case 0:
				break;
		}
	}
}

