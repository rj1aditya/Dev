#include <iostream>
#include<string>
#include<fstream>
using namespace std;
//#include"Controller.h"
 
class mamals{
private:
    std::string color;
    int legs;
public:
    mamals(std::string c,int l):legs(l),color(c){
    }
	mamals( int le = 0):legs(le)
	{}
    std::string getcolor(){
    return color;
    }
    friend mamals  operator+(mamals &m1 ,mamals &m2){
        int sum_of_legs =m1.legs+m2.legs;
        return mamals (m1.legs+m2.legs);
    }
	
	friend ostream& operator<<(ostream &cout,const mamals &obj)
	{
		cout<<obj.legs;
		return cout;
	}
};
 
int main(){
    mamals goat =mamals("brown",4);
    mamals sheep =mamals("white",4);
    std::cout<<"both mamals have total of "<<goat+sheep<<" legs"<<std::endl;
system("pause");
return 0;
}