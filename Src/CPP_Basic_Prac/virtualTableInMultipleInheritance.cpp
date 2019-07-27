#include<iostream>
using namespace std;

class Rail
{
	public:
	
	virtual void TrainInfo()
	{
	}
};

class Flight
{
	public:
	virtual void FlightInfo()
	{
	}
};

class Transport: public Rail, public Flight
{
	public:
	virtual void TrainInfo()
	{
		cout<<"Rail ticket"<<endl;
	}
	
	virtual void FlightInfo()
	{
		cout<<"Flight ticket"<<endl;
	}
	
	virtual void TransportInfo()
	{
		cout<<"Drived class virtual function called: "<<endl;
	}
};

int main()
{
	Rail *robj = new Transport;
	
	cout<<"try to call drived class virtual function using base class pointer: "<<endl;
	//robj->TransportInfo();
	Flight *fobj;
	
	robj->TrainInfo();
	fobj = dynamic_cast<Flight*>(robj);
	fobj->FlightInfo();
}