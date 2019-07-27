#include<iostream>
using namespace std;

class singleton
{
	private:
	static singleton obj;
	singleton()
	{}
	public:
	static singleton getInstance()
	{
		/*if( obj == NULL )
		{
			obj = new singleton;
		}*/
		singleton::obj;
		return obj;
	}
	void show()
	{
		cout<<"Kesari";
	}
};

int main()
{
	singleton obj = singleton::getInstance();
	obj.show();
}
	