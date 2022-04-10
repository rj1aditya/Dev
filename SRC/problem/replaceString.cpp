class Solution
{
public:
    /*    string findReplaceString(string s, vector<int>& indices, vector<string>& sources, vector<string>& targets) {
        string newS = s;
        int offset = 0;
        for( int i = 0; i < indices.size(); i++ )
        {
            int idx = indices[i];// + offset;
            string w = sources[i];
            int w_len = w.length();
            
            string t = targets[i];
            
            if( s.compare( idx, w_len, w) == 0 )
            {
                newS.erase(idx + offset, w_len);
                newS.insert(idx + offset, t);
                offset += t.length() - w_len; 
            }
            
        }
        return newS;
    }
*/
    string findReplaceString(string S, vector<int> &indexes, vector<string> &sources, vector<string> &targets)
    {
        string res = S;
        map<int, pair<string, string>> mp;
        int key = 0;
        for (int i = 0; i < indexes.size(); i++)
        {
            mp[indexes[i]] = make_pair(sources[i], targets[i]);
        }
        int dx = 0;
        for (auto itr : mp)
        {
            auto idx = itr.first;
            auto rec = itr.second;
            if (S.substr(idx, rec.first.size()) == rec.first)
            {
                res.erase(idx + dx, rec.first.size());
                res.insert(idx + dx, rec.second);
                dx += rec.second.size() - rec.first.size();
            }
        }
        return res;
    }
};

int main()
{
    Solution s1;
    string s = "abcde";
    vector<string> v{"a", "bb", "acd", "ace"};
    cout << s1.findReplaceString(s, v);
}