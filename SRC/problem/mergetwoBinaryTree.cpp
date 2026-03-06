/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {

public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
            
        // when both tree t1 and t2 are null
        if( root1 == nullptr && root2 == nullptr )
            return nullptr;
        
        int val = 0;
        // if both tree are not null we add their node element val
        if( root1 && root2 )
        {
            val = root1->val + root2->val;
        }
        // if root1 tree is null
        else if( !root1 )
             val = root2->val;
        //if root2 tree is null
        else
            val = root1->val;
        
        // create a new tree and assigh t1->val + t2->val
        TreeNode* root = new TreeNode(val);

        // this is taken because let say in traversal of t1 tree there may be no node in t2 and vice verca
        TreeNode* t1 = nullptr;
        TreeNode* t2 = nullptr;
        
        // this is taken because let say in traversal of t1 tree there may be no node in t2 and vice verca
        if( root2 && root2->left != nullptr)
            t2 = root2->left;
        if( root1 && root1->left != nullptr)
            t1 = root1->left;
        // this is taken because let say in traversal of t1 tree there may be no node in t2 and vice verca
        root->left = mergeTrees(t1, t2);
        
        // this is taken because let say in traversal of t1 tree there may be no node in t2 and vice verca
        t1 = nullptr;
        t2 = nullptr;
        if( root2 && root2->right != nullptr)
            t2 = root2->right;
        if( root1 && root1->right != nullptr)
            t1 = root1->right;
        // this is taken because let say in traversal of t1 tree there may be no node in t2 and vice verca
        root->right = mergeTrees(t1, t2);
        
        return root;

        
    }
};