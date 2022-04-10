#include<iostream>
#include<string>
using namespace std;

class gameSetting
{
	static gameSetting *_instance;
	int _brigthness;
	int _width;
	int _height;
	gameSetting():_brigthness(786),_width(75),_height(1300){}
	
	public:
	static gameSetting* getInstance()
	{
		if( _instance == NULL )
		{
			_instance = new gameSetting();
		}
		
		return _instance;
	}
	
	void setBrightness( int bg )
	{
		_brigthness = bg;
	}
	void setHeigth( int h )
	{
		_height = h;
	}
	void setWidth( int w )
	{
		_width = w;
	}
	
	void getConfig()
	{
		cout<<"brigthness: "<<_brigthness<<endl;
		cout<<"Height: "<<_height<<endl;
		cout<<"Width: "<<_width<<endl;
	}
	~gameSetting()
	{
		delete _instance;
		cout<<"Game End";
	}
};

gameSetting *gameSetting::_instance;

int main()
{
	gameSetting *setting = gameSetting::getInstance();
	setting->getConfig();
	
	//changeConfig();
	return 1;
}