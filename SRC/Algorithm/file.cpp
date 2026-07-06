struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

struct largeBST
{
    int size;
    int lowest;
    int highest;
    largeBST(int mini, int maxi, int s)
    {
        lowest = mini;
        highest = maxi;
        size = s;
    }
};



class Solution {
    
    largeBST func(Node* root)
    {
        if(!root)
            return largeBST(INT_MAX, INT_MIN, 0);
        
        largeBST l = func(root->left);
        largeBST r = func(root->right);
        
        if(root->data > l.highest && root->data < r.lowest)
        {
            int x = min(root->data, l.lowest);
            int y = max(root->data, r.highest);
            
            return largeBST(x, y, 1 + l.size+r.size);
        }
        
        return largeBST(INT_MIN, INT_MAX, max(l.size, r.size));
        
    }
    
  public:
    /*You are required to complete this method */
    // Return the size of the largest sub-tree which is also a BST
    int largestBst(Node *root) {
        // Your code here
        return func(root).size;    
    }
};