#include<memory>
#include<iostream>
using namespace std;

class Array
{
    int x;
    public:
    Array(int val = 0):x(val)
    {

    }
    int getValue()
    {
        return x;
    }
    void setValue(int val)
    {
        x = val;
    }
    ~Array(){
	    cout<<"Destrucotr\n";
	   }
};

int main()
{
    /*shared_ptr<Array> sPtr(new Array[10], 
		    [](Array *p)
		    {
		    	delete []p;
		    });*/
	unique_ptr<Array> sPtr(new Array[10]);
    for(int i = 0; i< 10; i++){
        sPtr.get()[i].setValue(i);
    }
    for(int i = 0; i< 10; i++){
        cout<<sPtr.get()[i].getValue()<<endl;
    }
    
}
