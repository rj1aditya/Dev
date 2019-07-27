#include<iostream>
#include<string>
#include<map>

using namespace std;

class MyMap
{
	int _id;
	string _name;
	public:
	MyMap( int id, string name ):_id(id),_name(name)
	{}
	
	const string& getName() const
	{
		return _name;
	}
	const int& getId() const
	{
		return _id;
	}
	
	bool operator< ( const MyMap &obj ) const
	{
		return ( obj._id > this->_id );
	}
};

/* Aditya 1
   Shubham 4
   Ashish 2
   Palash 5
*/

int main()
{
	map< MyMap, int > mObj;
	
	mObj.insert( make_pair( MyMap( 1, "Aditya" ), 10 ) );
	mObj.insert( make_pair( MyMap( 4, "Shubham" ), 15 ) );
	mObj.insert( make_pair( MyMap( 2, "Ashish" ), 102 ) );
	mObj.insert( make_pair( MyMap( 5, "Palash" ), 18 ) );

	for( map<MyMap,int>::iterator itr = mObj.begin(); itr != mObj.end(); itr++ )
	{
		cout<< itr->first.getName()<<" Roll no is: "<< itr->second<<endl;
	}
}