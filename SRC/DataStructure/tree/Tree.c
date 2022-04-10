#include<stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node* left;
    struct node* right;
}node;

struct node* head = NULL;
int nodeSize= sizeof(struct node);

struct node* createNewNode()
{
    struct node* ptr = (struct node*)malloc(nodeSize);
    ptr->left = NULL;
    ptr->right = NULL;
}

void Insert(struct node** ptr, struct node* new_node)
{
    if(*ptr == NULL)
    {
        *ptr = new_node;
    }
    else
    {
        if( new_node->data < (*ptr)->data )
        {
            Insert(&((*ptr)->left), new_node);
        }
        else
        {
            Insert(&((*ptr)->right), new_node);
        }
    }
}

void createTree()
{
    printf("\npress -1 to exit");
    printf("\nEnter the data: ");
    int num = 0;
    scanf("%d", &num);
    
    while(num != -1)
    {
        struct node* new_node = createNewNode();
        new_node->data = num;
        Insert(&head, new_node);
        printf("\npress -1 to exit");
        printf("\nEnter the data: ");
        scanf("%d", &num);
    }
}

void preOrderTraversal(struct node* ptr)
{
    if(ptr == NULL)
        return;
    printf("%d ",ptr->data);
    
    preOrderTraversal(ptr->left);
    preOrderTraversal(ptr->right);
}

void InOrderTraversal(struct node* ptr)
{
    if(ptr == NULL)
        return;

    InOrderTraversal(ptr->left);
    printf("%d ",ptr->data);
    InOrderTraversal(ptr->right);
}

void postOrderTraversal(struct node* ptr)
{
    if(ptr == NULL)
        return;

    postOrderTraversal(ptr->left);
    postOrderTraversal(ptr->right);
    printf("%d ",ptr->data);
}


int DisplayOption()
{
    printf("\n1. Create Tree");
    printf("\n2. preOrderTraversal Tree");
    printf("\n3. InOrderTraversal Tree");
    printf("\n4. postOrderTraversal Tree");
    printf("\n5. Delete Tree");
    printf("\n6. Search node in a Tree");
    printf("\n7. Delete a node in a Tree");
    printf("\n-1. Exit\n");
    int option = -1;
    scanf("%d", &option);
    return option;
}
void deleteTree(struct node* ptr)
{
    if(ptr != NULL)
    {
        deleteTree(ptr->left);
        deleteTree(ptr->right);
        printf("%d ", ptr->data);
        free(ptr);
        ptr = NULL;
    }
}

struct node* InPre(node *p) {
    while (p && p->right != NULL){
        p = p->right;
    }
    return p;
}
 
struct node* InSucc(node *p) {
    while (p && p->left != NULL){
        p = p->left;
    }
    return p;
}
int Height(struct node *p) 
{
    int x;
    int y;
    if (p == NULL){
        return 0;
    }
    x = Height(p->left);
    y = Height(p->right);
    return x > y ? x + 1 : y + 1;
}

struct node* deleteNode(struct node* ptr, int ele)
{
    if(ptr == NULL)
        return NULL;
    
    if( ptr->left == NULL && ptr->right == NULL )
    {
        if(ptr == head)
        {
            head == NULL;
        }
        free(ptr);
        return NULL;
    }
    
    if(ele < ptr->data)
        ptr->left = deleteNode(ptr->left, ele);
    else if (ele > ptr->data)
        ptr->right = deleteNode(ptr->right, ele);
    else
    {
        if (Height(ptr->left) > Height(ptr->right)){
            struct node* q = InPre(ptr->left);
            ptr->data = q->data;
            ptr->left = deleteNode(ptr->left, q->data);
        } else {
            struct node* q = InSucc(ptr->right);
            ptr->data = q->data;
            ptr->right = deleteNode(ptr->right, q->data);
        }
    }
    
}

struct node* searchNode(struct node* ptr, int ele)
{
    if(ptr == NULL)
        return ptr;

    if(ptr->data == ele)
        return ptr;

    else
    {
        if(ele<ptr->data)
            return searchNode(ptr->left, ele);
        else
            return searchNode(ptr->right, ele);
    }
}
int main()
{
    int option = 0;
    int len, ele;
    struct node* ptr = NULL;
    do{
        option = DisplayOption();
        switch (option)
        {
        case 1:
            createTree();
            break;
        case 2:
            preOrderTraversal(head);
            break;
        case 3:
            InOrderTraversal(head);
            break;
        case 4:
            postOrderTraversal(head);
            break;
        case 5:
            deleteTree(head);
            head = NULL;
            break;
        case 6:
            printf("\nEnter element value to be search in a tree DS: ");
            scanf("%d", &ele);
            ptr = searchNode(head, ele);
            if(!ptr)
            {
                printf("\nElement [%d] not present in the tree", ele);
            }
            else   
                printf("\nElement [%d] present in the tree", ele);
            break;
        case 7:
            printf("\nEnter element value to be delete from a tree DS: ");
            scanf("%d", &ele);
            ptr = deleteNode(head, ele);
        }
    }while(option != -1);
    deleteTree(head);
}