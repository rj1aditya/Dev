class DetectSquares {
    map<pair<int, int>, int> cordin;
    bool checkDiagonal(int x, int y, int a, int b)
    {
        // product taking coz might posible x - a or y - b comes -ve 
        int d1 = (x - a)*(x - a);
        int d2 = (y - b)*(y-b);
        return d1 == d2;
    }

public:
    DetectSquares() {
        
    }
    
    void add(vector<int> point) {
        cordin[ { point[0], point[1] } ]++;
    }
    
    int count(vector<int> point) {
        int res = 0;
        int a = point[0];
        int b = point[1];
        for( auto itr: cordin)
        {
            int x = itr.first.first;
            int y = itr.first.second;
            

            
            //same cordinates present in the map, we need to find a diagonal cordinates if present
            if( x == a && y == b )
                continue;
            else if( checkDiagonal(x, y, a, b))
            {
                // if any of the formed cordinates not presnt in the map then map will give 
                // 0 value so square 0 formed means nothing
                // else if any of the cordinates are presnt or present more than once than double 
                // or triple accordingly square will be formed
                res += cordin[{x, y}] * cordin[{x,b}] * cordin[{a,y}];
            }
        }
        return res;
        
    }
};
