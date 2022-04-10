#include<bits/stdc++.h>
using namespace std;

class node {
    public:
    char c;
    int end;
    node *child[26];
    node(char ch)
    {
        c = ch;
        end = 0;
        for(int i=0;i<26;++i)
            child[i] = NULL;
    }
};

class WordDictionary {

public:

    
    void Trie_insert(string s)
    {
        int index;
        node *curr = root;
        for( char ch: s)
        {
            index = ch-'a';
            if(!curr->child[index])
                curr->child[index] = new node(ch);
            curr = curr->child[index];
        }
        curr->end +=1;
    }
    
    bool Trie_search(string s,node *curr,int pos,int n)
    {        
        if(s[pos]=='.')
        {
            bool res = false;
            node *current = curr;
            for(int i=0;i<26;++i)
            {
                if(pos==n-1 && curr->child[i])
                {
                    current=curr->child[i];
                    res |= current->end>0?true:false;
                }
                else if(curr->child[i] && Trie_search(s,curr->child[i],pos+1,n))
                    return true;
            }
            return res;
        }
        else if(curr->child[s[pos]-'a'])
        {
            if(pos==n-1)
            {
                curr = curr->child[s[pos]-'a'];
                return curr->end>0?true:false;
            }
            return Trie_search(s,curr->child[s[pos]-'a'],pos+1,n);
        }
        return false;
    }
public:
    /** Initialize your data structure here. */
    node *root;
    WordDictionary()
    {
        root = new node('/');
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        Trie_insert(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return Trie_search(word,root,0,word.size());
    }
};


int main()
{
    WordDictionary wordDictionary1;
    wordDictionary1.addWord("bad");
    wordDictionary1.addWord("dad");
    wordDictionary1.addWord("mad");
    cout<<wordDictionary1.search("pad")<<endl; // return False
    cout<<wordDictionary1.search("bad")<<endl; // return True
    cout<<wordDictionary1.search(".ad")<<endl; // return True
    cout<<wordDictionary1.search("b..")<<endl; // return True
}