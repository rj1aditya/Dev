
#include<bits/stdc++.h>
using namespace std;
    /**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    ListNode* head = nullptr;    
public:
    Solution()
    {
        //head = nullptr;
    }
    void insertionSortList1() {
        head = insertionSortList(head);
    }
	ListNode* insertionSortList(ListNode *head) {
		if(head == nullptr) return head;

        //Creating a Dummy
		ListNode *a = new ListNode(0);

        //cur to head
		ListNode *cur = head;

        //as of now pre is pointing to dummy
		ListNode *pre = a;

        //next is null 
		ListNode *next = nullptr;

		while(cur != nullptr){

            // next will start from 2nd node in link list
			next = cur->next;

            // in starting pre is pointing to dummy only
			while(pre->next != nullptr && pre->next->val <= cur -> val){
				pre = pre -> next;
			}

            //here breaking the first node and pointing its next to null, since 2nd node is holding by the next pointer
			cur->next = pre->next;

            //here dummy->next will point to cur or head pointer
			pre->next = cur;

            //not impacted in first go
			pre = a;


			cur = next;
		}
		return a->next;
	}

    void push(int x)
    {
        ListNode* ptr = new ListNode(x);

        if(head == nullptr)
            head = ptr;
        else
        {
            ListNode* temp = head;
            while(temp->next != nullptr)
                temp = temp->next;

            temp->next = ptr;
        }
    }
    void display()
    {
        ListNode *ptr = head;
        while(ptr != NULL)
        {
            cout<<ptr->val<<" ";
            ptr = ptr->next;
        }
    }
};

int main()
{

    Solution s;
    s.push(4);
    s.push(2);
    s.push(1);
    s.push(3);
    s.display();
    s.insertionSortList1();
    cout<<endl;
    s.display();
}