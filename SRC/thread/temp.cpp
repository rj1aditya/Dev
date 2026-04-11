#include <bits/stdc++.h> 

class Node
{
    public:
    bool flag = false;
    Node* link[26];
    int cntWordEndWith;
    int cntPrefix;
    Node()
    {
        for(int i = 0; i < 26; i++)
            link[i] = nullptr;
        
        cntWordEndWith = 0;
        cntPrefix = 0;
    }

    bool checkChar(char ch)
    {
        return link[ch-'a'] != nullptr;
    }

    void insertChar(char ch)
    {
        link[ch-'a'] = new Node();
    }

    void increasePrefix()
    {
        cntPrefix++;
    }

    void increaseWordEndWith()
    {
        cntWordEndWith++;
    }

    void decreasePrefix()
    {
        cntPrefix++;
    }

    void decreaseWordEndWith()
    {
        cntWordEndWith++;
    }
    
    Node* next(char ch)
    {
        return link[ch-'a'];
    }

    void setTrue()
    {
        flag = true;
    }

    bool checkFlag()
    {
        return flag;
    }

    int getWordEndcount()
    {
        return cntWordEndWith;
    }

    int getWordPrefix()
    {
        return cntPrefix;
    }
};

class Trie{
    Node* trie;
    public:

    Trie(){
        // Write your code here.
        trie = new Node();
    }

    void insert(string &word){
        // Write your code here.
        Node* temp = trie;
        for(int i = 0; i < word.size(); i++)
        {
            char ch = word[i];
            if(!temp->checkChar(ch))
            {
                temp->insertChar(ch);
            }
            temp = temp->next(ch);
            temp->increasePrefix();
        }
        temp->increaseWordEndWith();
        temp->setTrue();
    }

    int countWordsEqualTo(string &word){
        // Write your code here.
        Node* temp = trie;
        for(int i = 0; i < word.size(); i++)
        {
            char ch = word[i];
            if(!temp->checkChar(ch))
            {
                return 0;
            }
            temp = temp->next(ch);
        }

        return temp->getWordEndcount();

    }

    int countWordsStartingWith(string &word){
        // Write your code here.
        Node* temp = trie;
        for(int i = 0; i < word.size(); i++)
        {
            char ch = word[i];
            if(!temp->checkChar(ch))
            {
                return 0;
            }
            temp = temp->next(ch);
        }

        return temp->getWordPrefix();
    }

    void erase(string &word){
        // Write your code here.
        Node* temp = trie;
        for(int i = 0; i < word.size(); i++)
        {
            char ch = word[i];
            if(!temp->checkChar(ch))
            {
                return;
            }
            temp = temp->next(ch);
            temp->decreasePrefix();
        }
        temp->decreaseWordEndWith();
    }
};
