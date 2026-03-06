#include<iostream>
using namespace std;

class Data
{
public:
	int LunNo;
	//string LunName;
	//int RaidGroup;
	Data *next;
	Data();
};


class LinkList
{
	Data *head;
	void InsertInstartingLinkList();
	void InsertAtEnd();
	void InsertInMiddle();
	void DeleteLastElement();
	void DeleteFirstElement();
	void DeleteElementFromMiddle();
	void InsertElement();
	void DeleteLinkList();
	void DeleteElement();
	void Display();
	void DeleteNode();
	void DeleteNodeAtGivenLoc();
	int Length();
	int getLength(Data*);
	bool IsPresent(Data*,int);
	bool SearchElement();
	void FromEnd(Data*,int);
	void NthNodeFromEnd();
	Data* MiddleElement();
	void NoofOccurance();
	int Occurance(Data*, int);
	void FindLoop();
	void FindLengthOfLoop(Data*);
	void IsPalindrome(Data*);
	void FindPalindrome(Data*);
	void Reverse();
	void RemoveDuplicatesFromSortedLL();
	void RemoveDuplicatesFromUnsortedLL();
	void SwappingNode();
public:
	void start();
	LinkList();
	~LinkList();
};
