class MaxStack {
    multimap<int, list<int>::iterator> mm;
    list<int> st;
public:
    MaxStack() {
        // Implement function here
    }

    void push(int x) {
        // Implement function here
        st.push_back(x);
        auto it = st.end();
        it--;
        mm.insert({x, it});
    }

    int pop() {
        // Implement function here
        int val = st.back();
        auto it = mm.upper_bound(val);
        it--;
        mm.erase(it);
        st.pop_back();
        return val;
    }

    int top() {
        // Implement function here
        
        return st.back();
    }

    int peekMax() {
        // Implement function here
        auto it = mm.end();
        it--;
        
        return it->first;
    }

    int popMax() {
        // Implement function here
        auto it = mm.end();
        it--;
        int val = it->first;
        mm.erase(it);
        st.erase(it->second);
        return val;
    }
};
