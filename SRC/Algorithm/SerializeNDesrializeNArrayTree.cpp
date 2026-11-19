/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Codec {
public:

    /*
        IDEA:
        -----
        We perform a Preorder DFS.

        For every node, we store:
            1. Node value
            2. Number of children

        Example:

                  1
               /  |  \
              3   2   4
             / \
            5   6

        Serialized String:
        ------------------
        1 3 3 2 5 0 6 0 2 0 4 0

        Explanation:
        1 has 3 children
        3 has 2 children
        5 has 0 children
        6 has 0 children
        2 has 0 children
        4 has 0 children

        During deserialization,
        after reading a node we already know
        exactly how many recursive calls are needed
        to build its children.
    */

    //---------------------- Serialize ----------------------//

    void dfsSerialize(Node* root, string &ans)
    {
        if (root == nullptr)
            return;

        // Store current node value
        ans += to_string(root->val) + " ";

        // Store number of children
        ans += to_string(root->children.size()) + " ";

        // Serialize every child
        for (Node* child : root->children)
            dfsSerialize(child, ans);
    }

    string serialize(Node* root)
    {
        if (root == nullptr)
            return "";

        string ans;

        dfsSerialize(root, ans);

        return ans;
    }

    //---------------------- Deserialize ----------------------//

    Node* dfsDeserialize(vector<string> &tokens, int &idx)
    {
        // Read current node value
        int value = stoi(tokens[idx++]);

        // Read how many children this node has
        int childCount = stoi(tokens[idx++]);

        Node* root = new Node(value);

        // Build exactly 'childCount' children
        for (int i = 0; i < childCount; i++)
        {
            root->children.push_back(
                dfsDeserialize(tokens, idx)
            );
        }

        return root;
    }

    Node* deserialize(string data)
    {
        if (data.empty())
            return nullptr;

        // Split string into tokens
        vector<string> tokens;
        stringstream ss(data);
        string token;

        while (ss >> token)
            tokens.push_back(token);

        int idx = 0;

        return dfsDeserialize(tokens, idx);
    }
};