#include<vector>
#include<algorithm>
#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<map>
#include <chrono>
using namespace std;

enum class VehicleType
{
	TWO_WHEELER,
	FOUR_WHEELER
};

class Vehicle
{

	public:
	VehicleType vhclType;
	string vhclNumber;
	Vehicle(VehicleType vt, string vn):vhclType(vt), vhclNumber(vn)
	{

	}
};

class parkingSpotLookupStrategy;

enum class ParkingSpotType
{
	TWO_WHEELER,
	FOUR_WHEELER
};

enum class ParkingSpoStatus
{
	FREE,
	OCCUPIED
};

class ParkingSpot
{
	ParkingSpotType prkSpotType;
	int id;
	ParkingSpoStatus prkSpotStatus;
	public:
	ParkingSpot(ParkingSpotType pst, int i, ParkingSpoStatus pss):prkSpotType(pst), id(i), prkSpotStatus(pss)
	{}

	bool checkStatus()
	{
		return prkSpotStatus==ParkingSpoStatus::FREE;
	}

	void setOccupied()
	{
		prkSpotStatus = ParkingSpoStatus::OCCUPIED;
	}

	void setFree()
	{
		prkSpotStatus=ParkingSpoStatus::FREE;
	}
};

class parkingSpotLookupStrategy
{
	public:
	virtual ParkingSpot* getParkingSpot(vector<ParkingSpot*> parkingSpots)=0;
};

class nearbyParkingSpot: public parkingSpotLookupStrategy
{
	public:
	ParkingSpot* getParkingSpot(vector<ParkingSpot*> parkingSpots) override
	{
		for(int i = 0; i < parkingSpots.size(); i++)
		{
			if(parkingSpots[i]->checkStatus())
				return parkingSpots[i];
		}

		return nullptr;
	}
};

class randomParkingSpot: public parkingSpotLookupStrategy
{
	ParkingSpot* getParkingSpot(vector<ParkingSpot*> parkingSpots) override
	{
		for(int i = 0; i < parkingSpots.size(); i++)
		{
			if(parkingSpots[i]->checkStatus())
				return parkingSpots[i];
		}

		return nullptr;
	}
};

class ParkingSpotManager
{
	vector<ParkingSpot*> parkingSpots;
	parkingSpotLookupStrategy *strategy;
	mutex mtx;


	public:
	ParkingSpotManager(vector<ParkingSpot*> prkS, parkingSpotLookupStrategy* strtgy):parkingSpots(prkS), strategy(strtgy)
	{}

	ParkingSpot* getSpot()
	{
		lock_guard<mutex> lg(mtx);
		ParkingSpot* ps = strategy->getParkingSpot(parkingSpots);
		if(ps == nullptr)
			return nullptr;
		
		ps->setOccupied();
		return ps;
	}

	void FreeSpot(ParkingSpot* ps)
	{
		ps->setFree();
	}


	bool hasFreeSpot()
	{
		lock_guard<mutex> lg(mtx);
		auto res = any_of(parkingSpots.begin(), parkingSpots.end(), [](const auto& ps){
			return ps->checkStatus();
		});

		return res;
	}
};

class twoWheelerParkingSpotManager: public ParkingSpotManager
{
	public:
	twoWheelerParkingSpotManager(vector<ParkingSpot*> prkS, parkingSpotLookupStrategy* strtgy):ParkingSpotManager(prkS, strtgy)
	{}
};

class fourWheelerParkingSpotManager: public ParkingSpotManager
{
	public:
	fourWheelerParkingSpotManager(vector<ParkingSpot*> prkS, parkingSpotLookupStrategy* strtgy):ParkingSpotManager(prkS, strtgy)
	{}
};


class ParkingLevel
{
	map<VehicleType, ParkingSpotManager*> m;
	int parkinglevel;
	public:
	ParkingLevel(map<VehicleType, ParkingSpotManager*> &mm, int &prklvl): m(mm), parkinglevel(prklvl)
	{}

	int getLevelNumber()
	{
		return parkinglevel;
	}


	bool isParkingSpotAvailable(VehicleType vt)
	{
		return m[vt]->hasFreeSpot();
	}

	ParkingSpot* getSpot(VehicleType vt)
	{
		return m[vt]->getSpot();
	}

	void freeSpot(VehicleType vt, ParkingSpot* ps)
	{
		m[vt]->FreeSpot(ps);
	}
};


class ParkingTicket
{
	Vehicle* vh;
	ParkingSpot *ps;
	ParkingLevel* parkingLvl;
	std::chrono::steady_clock::time_point entryTime;
	public:

	ParkingTicket(Vehicle* v, ParkingSpot* p, ParkingLevel* pl): vh(v), ps(p), parkingLvl(pl)
	{
		entryTime = chrono::steady_clock::now();
	}

	Vehicle* getVehicle() const
    {
        return vh;
    }

    ParkingLevel* getLevel() const
    {
        return parkingLvl;
    }

    ParkingSpot* getSpot() const
    {
        return ps;
    }

    std::chrono::steady_clock::time_point getEntryTime() const
    {
        return entryTime;
    }
};

class ParkingBuilding
{
	vector<ParkingLevel*> levels;
	public:
	ParkingBuilding(vector<ParkingLevel*> &b): levels(b)
	{}

	ParkingTicket* allocate(Vehicle* vh)
	{
		for(auto x: levels)
		{
			if(x->isParkingSpotAvailable(vh->vhclType))
			{
				ParkingSpot* ps = x->getSpot(vh->vhclType);
				if(ps != nullptr)
				{
					return new ParkingTicket(vh, ps, x);
				}
			}
		}
	}

	void release(ParkingTicket* t)
	{
		ParkingLevel* pl = t->getLevel();
		pl->freeSpot(t->getVehicle()->vhclType, t->getSpot());
		
	}
};



class EntranceGate
{
	public:
	ParkingTicket* enter(ParkingBuilding* pb, Vehicle* vh)
	{
		return pb->allocate(vh);
	}
};

class PricingStrategy
{
	public:
	virtual double compute(ParkingTicket* t)=0;
};

class fixedPricing: PricingStrategy
{
	public:
	double compute(ParkingTicket* t)
	{
		return 100.0;
	}

};


class CostComputation
{
	PricingStrategy* priceStr;
	public:
	CostComputation(PricingStrategy* p): priceStr(p)
	{}

	double compute(ParkingTicket* t)
	{
		return priceStr->compute(t);
	}
};


class PaymentStrtegy
{
	public:
	virtual bool pay(double amt)=0;
};

class phonePay:public PaymentStrtegy
{
	public:
	bool pay(double amt)
	{
		return true;
	}
};

class ExitGate
{
	CostComputation* cst;
	//PaymentStrtegy* payment;
	//ParkingTicket* prkTckt;
	public:
	ExitGate(CostComputation* c, PaymentStrtegy* pay, ParkingTicket* t): cst(c){} 

	double computeAmt(ParkingTicket* t)
	{
		return cst->compute(t);
	}

	void completeExit(PaymentStrtegy* p, ParkingTicket* t, ParkingBuilding* pb)
	{
		p->pay(computeAmt(t));
		pb->release(t);
	}
};

class ParkingLot
{
	ParkingBuilding* prkngBld;
	EntranceGate* EnterGate;
	ExitGate* ExtGate;
	public:
	ParkingLot(ParkingBuilding* pb, EntranceGate* entrgate, ExitGate* ExtG): prkngBld(pb), EnterGate(entrgate), ExtGate(ExtG)
	{}

	ParkingTicket* enterVehicle(Vehicle v)
	{
		return prkngBld->allocate(&v);
	}

	void exitVehicle(ParkingTicket* pt, PaymentStrtegy* p)
	{
		ExtGate->completeExit(p, pt, prkngBld);
	}
};


int main()
{
	ParkingLevel* parkinglvls = new ParkingLevel();
	ParkingBuilding* prkngBld = new ParkingBuilding();
}
