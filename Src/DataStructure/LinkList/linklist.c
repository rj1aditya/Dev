#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include <stdbool.h>
typedef struct node
{
    struct  node *next;
    int data;
}node;
int nodeSize = sizeof(struct node);
static struct node *head = NULL;

static int DisplayOption();
static void cleanupnode();
static void exit_from_create_ll(int sig);
static void create_ll();
static void Delete_ll();
static void Display_ll();
static void AddNodeBeforeNode();
static void AddNodeAtBeginning();
static void AddNodeAtEnd();
static void insert_before();
static void SwapNodes(int x, int y);
static void insert_after();
static void delete_beg();
static void delete_end();
static void delete_node();
static void delete_after();
static void sort();
static void reverse();
static struct node* NthNodeFromEnd(struct node* ptr, int ele);
static struct node* reverse_recursive();
static int length_recursive(struct node* ptr);
static void findLoop();
int Occurance(struct node* temp, int val);
static struct node* MiddleElement();
struct node* findPalindrone(struct node* ptr, int* palindrone);
static void SwappingNode();

static struct node* create_new_node()
{
    struct node* new_node = (struct node*)malloc(nodeSize);
    printf("\nEnter the data: ");
    int num = 0;
    scanf("%d", &num);
    new_node->data = num;
    new_node->next = NULL;

    return new_node;
}

static void SwappingNode()
{
    int x, y;
    Display_ll();
    printf("\nEnter any 2 nodes to be swapped: ");
    scanf("%d %d", &x, &y);

    struct node* first= NULL, *second=NULL;
    struct node* first_prev= NULL, *second_prev=NULL;
    struct node* ptr= head;
    struct node* ptr_prev= NULL;

    while(ptr != NULL)
    {
        
        if(ptr->data == x)
        {
            first = ptr;
            first_prev = ptr_prev;
        }
        else if( ptr->data == y)
        {
            second = ptr;
            second_prev = ptr_prev;
        }
        ptr_prev = ptr;
        ptr = ptr->next;
    }

    if( first != second && (first != NULL && second != NULL) )
    {
        if( first_prev != NULL )
        {
            first_prev->next = second;
        }
        else
            head = second;

        if( second_prev != NULL )
        {
            second_prev->next = first;
        }
        else  
            head = first;

        ptr = first->next;
        first->next = second->next;
        second->next = ptr;
    }
}
static void SwapNodes(int x, int y)
{
    struct node* first= NULL, *second=NULL;
    struct node* first_prev= NULL, *second_prev=NULL;
    struct node* ptr= head;
    struct node* ptr_prev= NULL;

    while(ptr != NULL)
    {
        
        if(ptr->data == x)
        {
            first = ptr;
            first_prev = ptr_prev;
        }
        else if( ptr->data == y)
        {
            second = ptr;
            second_prev = ptr_prev;
        }
        ptr_prev = ptr;
        ptr = ptr->next;
    }

    if( first != second && (first != NULL && second != NULL) )
    {
        if( first_prev != NULL )
        {
            first_prev->next = second;
        }
        else
            head = second;

        if( second_prev != NULL )
        {
            second_prev->next = first;
        }
        else  
            head = first;

        ptr = first->next;
        first->next = second->next;
        second->next = ptr;
    }
}

struct node* findPalindrone(struct node* ptr, int* palindrone)
{
    struct node* temp = head;
    *palindrone = 1;

    if( ptr->next != NULL )
    {
        temp = findPalindrone(ptr->next, palindrone);

    }

    if(ptr->data == temp->data && *palindrone )
    {
        *palindrone=1;
        return temp->next;
    }
    else
    {
        *palindrone = 0;
        return temp->next; 
    }
}
static void FindLengthOfLoop(struct node* fast)
{
    struct node* ptr = fast->next;
    int length = 0;
    while(ptr != fast)
    {
        ++length;
        ptr = ptr->next;
    }
    printf("\nloop length is[%d]",length);
}
int Occurance(struct node* temp, int val)
{
	if( temp != NULL && temp->data == val )
	{
		return 1 + Occurance( temp->next, val );
	}
	else if( temp != NULL )
		Occurance(temp->next,val);
	else
		return 0;
}

static struct node* MiddleElement()
{
	struct node*fast_ptr = head;
	struct node*slow_ptr = head;

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

	printf("\nMiddle node is:[%d] ",slow_ptr->data);
	return slow_ptr;
}

void findLoop()
{
	//this line of code is just to make looped link list ..//
	struct node *temp = head;
	struct node *temp1 = head;

	while( temp->next != NULL )
		temp = temp->next;

	temp->next = temp1->next->next;
	// looped link list ended

    struct node *fast = head, *slow = head;

    while(fast != NULL && fast->next != NULL )
    {
        fast = fast->next->next;
        slow = slow->next;
        if( fast == slow )
        {
            printf("\nLoop detected in the Linked lists");
	        //removing loop from link list
			FindLengthOfLoop(fast);
			temp->next = NULL;
            break;
        }
    }
    printf("\nLoop not detected in the Linked lists");
}
struct node* NthNodeFromEnd(struct node* ptr, int ele)
{
    static int nth = 0;
    static struct node* ptr1 = NULL;

    if(ptr->next != NULL)
    {
        ptr1 = NthNodeFromEnd(ptr->next, ele);
    } 
    if(++nth == ele)
        return ptr1=ptr;
    else if( nth > ele)
        return ptr1;
    else
        return NULL;
    
}

static int length_recursive(struct node* ptr)
{
    if(ptr != NULL )
    {
        return 1+length_recursive(ptr->next);
    }
    else
        return 0;
}

static void reverse()
{
    struct node* curr_node = head;
    struct node* next_node = NULL;
    struct node* prev_node = NULL;

    while(curr_node != NULL)
    {
        next_node = curr_node->next;
        curr_node->next = prev_node;
        prev_node = curr_node;
        curr_node = next_node;
    }
    //curr_node->next = prev_node;
    head = prev_node;
}

//reverse_recursive is like while terminating or unwinding stack, sending future person in past
static struct node* reverse_recursive(struct node* curr_node)
{
    struct node* ptr;
    if( curr_node->next == NULL )
    {
        head = curr_node;
        return head;
    }

    if( curr_node->next != NULL )
        ptr = reverse_recursive(curr_node->next);
        
    ptr->next = curr_node;
    curr_node->next = NULL;
    return curr_node;
}

static void insert_before()
{
    Display_ll();
    printf("\nEnter node before you wanted to insert an element: ");
    int nodeElement;
    scanf("%d", &nodeElement);


    struct node* curr_node = head;
    struct node* prev_node = NULL;
    while(curr_node != NULL && curr_node->data != nodeElement )
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    if(curr_node == NULL)
    {
        printf("\nInvalid node element value entered");
        return;
    }
    else
    {
        if(prev_node == NULL)
        {
            AddNodeAtBeginning();
            return;
        }
        struct node* new_node = create_new_node();
        new_node->next = curr_node;
        prev_node->next = new_node;
    }

}

static void insert_after()
{
    Display_ll();
    printf("\nEnter node after you wanted to insert an element: ");
    int nodeElement;
    scanf("%d", &nodeElement);
    

    struct node* curr_node = head;

    while(curr_node != NULL && curr_node->data != nodeElement)
    {
        curr_node = curr_node->next;
    }
    if(curr_node == NULL)
    {
        printf("\nInvalid node element value entered");
        return;
    }
    struct node* new_node = create_new_node();
    new_node->next = curr_node->next;
    curr_node->next = new_node;
}

static void delete_beg()
{
    if(head == NULL)
    {
        printf("\nEmpty link list");
        return;
    }

    struct node* ptr = head;
    head = head->next;
    free(ptr);
}

static void delete_end()
{
    if(head == NULL)
    {
        printf("\nEmpty link list");
        return;
    }

    struct node* curr_node = head;
    struct node* prev_node = curr_node;

    while( curr_node->next != NULL )
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    if(curr_node == head)
        head = NULL;
    
    prev_node->next = NULL;
    free(curr_node);
    curr_node = NULL;
}

static void delete_node()
{
    if(head == NULL)
    {
        printf("\nEmpty link list");
        return;
    }

    int nodeElement;
    Display_ll();
    printf("\nEnter element to delete: ");
    scanf("%d", &nodeElement);

    struct node* curr_node = head;
    struct node* prev_node = curr_node;

    while( curr_node->data != nodeElement && curr_node->next != NULL )
    {
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    if( curr_node->data != nodeElement )
    {
        printf("\nNode element not present in the link list");
        return;
    }
    if( curr_node == head )
    {
        //head = NULL;
        delete_beg();
        return;
    }
    prev_node->next = curr_node->next;
    free(curr_node);
}
static void delete_after()
{
    if(head == NULL)
    {
        printf("\nEmpty link list");
        return;
    }

    struct node* curr_node = head;
    Display_ll();
    int nodeElement;
    printf("\nEnter nodeElement value after that node to be deleted: ");
    scanf("%d", &nodeElement);

    while(curr_node->data != nodeElement && curr_node->next != NULL)
    {
        curr_node = curr_node->next;
    }
    if( curr_node->data != nodeElement )
    {
        printf("\nNode element not present in the link list");
        return;
    }
    else if( curr_node->next == NULL )
    {
        printf("\n[%d] is the last element in the link list", curr_node->data);
        return;
    }
    struct  node* ptr = curr_node->next;
    curr_node->next = ptr->next;
    free(ptr);

}
//Sorting using selection sort method, here swapNodes function is used which takes k time complexity
// So BigO(n^2+k) is time complexity
static void sort()
{
    struct node* outerNode = head;
    struct node* innerNode = NULL;
    struct node* prev_node = NULL;
    int flag = 0;
    struct node Dummy;
    Dummy.next = NULL;

    while(outerNode != NULL && outerNode->next != NULL )
    {
        struct node* min_node = outerNode;
        innerNode = outerNode->next;
        struct node Dummy;
        Dummy.next = min_node;
        while(innerNode != NULL)
        {
            if(innerNode->data < min_node->data)
            {
                min_node = innerNode;
            }
            innerNode=innerNode->next;
        }
        SwapNodes(outerNode->data, min_node->data);
        if(Dummy.next == min_node)
            outerNode = outerNode->next;
        else
            outerNode = min_node;
    }
}




void AddNodeAtBeginning()
{
    struct node* new_node = create_new_node();
    new_node->next = head;
    head = new_node;
}

void AddNodeAtEnd()
{
    struct node* new_node = create_new_node();

    struct node* ptr = head;
    while(ptr->next != NULL)
    {
        ptr = ptr->next;
    }
    ptr->next = new_node;
}


void cleanupnode()
{
    printf("\ncleaning up the nodes");
    struct node* ptr = head;
    while(head!=NULL)
    {
        ptr = head;
        head = head->next;
        free(ptr);
    }
}

static void exit_from_create_ll(int sig)
{
    printf("\nctrl-c pressed");
    cleanupnode();
    exit(-1);
    return;
}

void create_ll()
{

    printf("\npress -1 to exit");
    printf("\nEnter the data: ");
    int num = 0;
    scanf("%d", &num);
    struct node* new_node;
    struct node* ptr;

    while(num != -1)
    {
        new_node = (struct node*)malloc(nodeSize);
        new_node->data = num;
        new_node->next = NULL;
        if( head == NULL )
        {
            head = new_node;
        }
        else
        {
            ptr = head;
            while( ptr->next != NULL )
                ptr = ptr->next;
            ptr->next = new_node;
        }
        printf("\npress -1 to exit");
        printf("\nEnter the data: ");
        scanf("%d", &num);
    }
}

static void Delete_ll()
{
    struct node* ptr = head;
    ptr = head;
    printf("Deleting Linked list nodes: ");
    while( head != NULL )
    {
        head = head->next;
        printf("[%d]->", ptr->data);
        free(ptr); 
        ptr = head;
    }
    printf("NULL\n");
    getchar();
}

static void Display_ll()
{
    struct node* ptr = head;
    ptr = head;
    printf("\nLinked list nodes: ");
    while( ptr != NULL )
    {
        printf("[%d]->", ptr->data);
        ptr = ptr->next;
    }
    printf("NULL\n");
    getchar();
}

int main()
{
    signal(SIGINT, exit_from_create_ll);
    int option = 0;
    int len, ele;
    struct node* ptr = NULL;
    do{
        option = DisplayOption();
        switch (option)
        {
        case 1:
            create_ll();
            break;

        case 2:
            Display_ll();
            break;
        
        case 3:
            Delete_ll();
            break;

        case 4:
            cleanupnode();
            break;
        case 5:
            AddNodeAtBeginning();
            break;
        case 6:
            AddNodeAtEnd();
            break;
        case 7:
            insert_before();
            break;

        case 8:
            insert_after();
            break;
        
        case 9:
            delete_beg();
            break;

        case 10:
            delete_end();
            break;
        case 11:
            delete_node();
            break;
        case 12:
            delete_after();
            break;

        case 13:
            sort();
            break;
        case 14:
            reverse();
            break;
        case 15:
            ptr = reverse_recursive(head);
            ptr = NULL;
            break;
        case 16:
            len = length_recursive(head);
            printf("\nLength[%d]", len);
            break;
        case 17:
            printf("\nEnter location no to be search from the end:");
            Display_ll();
            scanf("%d", &ele);
            ptr = NthNodeFromEnd(head, ele);
            if(ptr!=NULL)
                printf("\n nth element[%d] from last is [%d]", ele, ptr->data);
            break;
        case 18:
            findLoop();
            break;
        case 19:
            Display_ll();
	        printf("\nEnter an element to find the no of occurance in link list: ");
	        scanf("%d", &ele);
	        ele = Occurance(head,ele);
            printf("\nno of occurance in link list:[%d]", ele);
            break;
        case 20:
            ptr=MiddleElement();
            break;
        case 21:
            findPalindrone(head, &ele);
            if(ele != 0)
                printf("\nLinked list is palindrone");
            else
                printf("\nLinked list is not palindrone");
            break;
        case 22:
            SwappingNode();
            break;
        default:
            break;
        }

    }while(option != 4);
}


int DisplayOption()
{
    printf("\n1. Create link list");
    printf("\n2. Display link list");
    printf("\n3. Delete link list");
    printf("\n5. Add a node at the beginning");
    printf("\n6. Add a node at the end");
    printf("\n7: Add the node before a given node");
    printf("\n8: Add the node after a given node");
    printf("\n9: Delete a node from the beginning");
    printf("\n10: Delete a node from the end");
    printf("\n11: Delete a given node");
    printf("\n12: Delete a node after");
    printf("\n13: sort");
    printf("\n14: Reverse link list");
    printf("\n15: Reverse link list recursively");
    printf("\n16: length recursively");
    printf("\n17: nth node from last");
    printf("\n18: findLoop");
    printf("\n19: Occurance");
    printf("\n20: MiddleElement");
    printf("\n21: findPalindrone");
    printf("\n22: swap");
    printf("\n4. Exit\n");
    int option = 0;
    scanf("%d", &option);
    return option;
}
