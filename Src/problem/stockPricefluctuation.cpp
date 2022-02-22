class StockPrice {
    //for storing the stock price with the timestamp
    map<int,int> sp;
    //since this is the ordered set in ascending order
    //will use to get min and max
    multiset<int> m;
    
    int currTimeStamp;
public:
    StockPrice() {
        currTimeStamp = 0;
    }
    
    void update(int timestamp, int price) {
        
        if( sp[timestamp] )
        {
            m.erase( m.find(sp[timestamp]) );
        }
        sp[timestamp] = price;
        m.insert(price);
        currTimeStamp = max(currTimeStamp, timestamp );
    }
    
    int current() {
        return sp[currTimeStamp];
    }
    
    int maximum() {
        return *m.rbegin();
    }
    
    int minimum() {
        return *m.begin();
    }
};