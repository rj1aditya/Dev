#include<iostream>
using namespace std;

class Node
{
	public:
	int data;
	Node *left;
	Node *right;
};

Node *head = NULL;
Node* minValueNode( Node *ptr );
Node* DeleteElement( Node* tree, int val );
Node* Insert( Node*, int );
void Inorder( Node* );
void Preorder( Node* );
void Postorder( Node* );
Node* SearchElement( Node*, int );
Node* LargestElement( Node* tree );
Node* SmallestElement( Node* tree );
void DeleteTree( Node *tree );
int totalNodes(Node *tree);
int Height( Node *tree );
void printGivenLevel( Node*, int );
void  printLevelOrder( Node* );

int main()
{
	int option;
	Node* temp;
	do
	{
		printf("\n ******MAIN MENU******* \n");
		printf("\n 1. Insert Element");
		printf("\n 2. Preorder Traversal");
		printf("\n 3. Inorder Traversal");
		printf("\n 4. Postorder Traversal");
		printf("\n 5. Find the smallest element");
		printf("\n 6. Find the largest element");
				printf("\n 7. Delete an element");
		printf("\n 8. Count the total number of nodes");
		printf("\n 9. Count the total number of external nodes");
		printf("\n 10. Count the total number of internal nodes");
		printf("\n 11. Determine the height of the tree");
		printf("\n 12. Find the mirror image of the tree");
		printf("\n 13. Delete the tree");
		printf("\n 14. Search element in the tree");
		printf("\n 15. BFS or print tree in level format");
		printf("\n 16. Exit");
		printf("\n\n Enter your option : ");
		scanf("%d", &option);
		switch(option)
		{
			case 1:
				int val;
				
				cout<<"Enter value to be insert in the tree:";
				cin>>val;
				head = Insert( head, val );
				
				/*Node *ptr;
				ptr = new Node;
				ptr->data = 45;
				ptr->left = new Node;
				ptr->left->data = 40;
				ptr->left->right = NULL;
				ptr->right = new Node;
				ptr->right->data = 50;
				ptr->right->left = NULL;
				ptr->left->left = new Node;
				ptr->left->left->data = 33;
				ptr->left->left->left = NULL;
				ptr->left->left->right = NULL;
				ptr->right->right = new Node;
				ptr->right->right->data = 67;
				ptr->right->right->right = NULL;
				ptr->right->right->left = NULL;
				
				head = ptr;
								*/
				break;
			case 2:
				cout<<"Preorder of tree: ";
				Preorder( head );
				break;
			case 3:
				cout<<"Inorder of tree: ";
				Inorder( head );
				break;
			case 4:
				cout<<"Postorder of tree: ";
				Postorder( head );
				break;
			case 5:
				temp = SmallestElement( head );
				cout<<"SmallestElement in the tree is: "<<temp->data<<endl;
				break;
			case 6:
				temp = LargestElement( head );
				cout<<"LargestElement in the tree is: "<<temp->data<<endl;
				break;
			case 7:
				cout<<"Enter element to be deleted from the tree: "<<endl;
				cin>>val;
				head = DeleteElement( head, val );
				break;
			case 8:
				val = totalNodes( head );
				cout<<"total no of nodes in the tree is: "<<val;
				break;
			case 11:
				val = Height( head );
				cout<<"Height of the tree is: "<<val;
				break;
			case 13:
				cout<<"Deleting node: "<<endl;
				DeleteTree( head );
				break;
			case 14:
				cout<<"Enter value to be search in the tree:"<<endl;
				cin>>val;
				temp = SearchElement( head, val );
				if( temp != NULL )
					cout<<"Element present in the tree"<<endl;
				else
					cout<<"Element not present in the tree"<<endl;
				break;
			case 15:
				printLevelOrder( head );
				break;
			default:
			cout<<"Tree"<<endl;
		}
	}while(option!=16);
}

Node* Insert( Node* tree, int val )
{
	Node *temp, *parentptr, *nodeptr;
	temp = new Node;
	temp->data = val;
	temp->left = NULL;
	temp->right = NULL;
	
	if( tree == NULL )
	{
		tree = temp;
		tree->left = NULL;
		tree->right = NULL;
	}
	else
	{	
		nodeptr = tree;
		parentptr = NULL;
		while( nodeptr != NULL )
		{
			parentptr = nodeptr;
			if( val < parentptr->data )
				nodeptr = nodeptr->left;
						else
				nodeptr = nodeptr->right;
		}
		if( val < parentptr->data )
			parentptr->left = temp;
		else
			parentptr->right = temp;
	}
	return tree;
}

void Preorder( Node* ptr )
{
	if( ptr != NULL ){
		cout<<ptr->data<<" ";
		Preorder( ptr->left );
		Preorder( ptr->right );
	}
}


void Postorder( Node* ptr )
{
	if( ptr != NULL ){
		Preorder( ptr->left );
		Preorder( ptr->right );
		cout<<ptr->data<<" ";
	}
}

void Inorder( Node* ptr )
{
	if( ptr != NULL )
	{
		Inorder( ptr->left );
		cout<<ptr->data<<" ";
		Inorder( ptr->right );
	}
}

Node* SmallestElement( Node* tree )
{
	if( tree == NULL || tree->left == NULL )
		return tree;
	else
		return SmallestElement( tree->left );
}

Node* LargestElement( Node* tree )
{
	if( tree == NULL || tree->right == NULL )
		return tree;
	else
		return LargestElement( tree->right );
}

Node* SearchElement( Node* tree, int val )
{
	if( tree == NULL || tree->data == val )
		return tree;
	else
	{
		if( val < tree->data )
			return SearchElement( tree->left, val );
		else
			return SearchElement( tree->right, val );
	}
}

void DeleteTree( Node *tree )
{
	if ( tree != NULL )
	{
		DeleteTree( tree->left );
		DeleteTree( tree->right );
		cout<<tree->data<< " ";
	}
}

int totalNodes(Node *tree)
{
	if(tree==NULL)
		return 0;
	else
		return(totalNodes(tree->left) + totalNodes(tree->right) + 1);
}

Node* minValueNode( Node *ptr )
{
	if( ptr->left != NULL )
	{
		ptr = ptr->left;
	}
	
	return ptr;
}

Node* DeleteElement( Node* tree, int val )
{
	if( tree == NULL )
		return tree;
	
	if( val < tree->data )
		tree->left = DeleteElement( tree->left, val );
	else if( val > tree->data )
		tree->right = DeleteElement( tree->right, val );
	
	else
	{	
		if( tree->left == NULL )
		{
			Node *temp = tree->right;
			delete tree;
			return temp;
		}
		else if( tree->right == NULL )
		{
			Node* temp = tree->left;
			delete tree;
			return temp;
					}
		
		Node *temp = minValueNode( tree->right );
		tree->data = temp->data;
		
		tree->right = DeleteElement( tree->right, temp->data );
	}
}

int Height( Node *tree )
{
	int leftHeight,rightHeight;
	
	if( tree == NULL )
		return 0;
	else
	{
		leftHeight = Height( tree->left );
		rightHeight = Height( tree->right );
	}
	
	if( leftHeight < rightHeight )
		return rightHeight + 1;
	else
		return leftHeight + 1;
}

void printLevelOrder( Node *tree )
{
	int h = Height( tree );
	for( int i = 1; i <= h; i++ )
	{
		printGivenLevel( tree, i );
	}
}

void printGivenLevel( Node *tree, int level )
{
	if( tree == NULL )
		return;
	if( level == 1 )
	{
		cout<<tree->data<<" ";
	}
	else if( level > 1 )
	{
		printGivenLevel( tree->left, level - 1 );
	}
}