
'''//Cab Sharing Service
#include<iostream>
#include<map>
#include<vector>
#include<queue>
#include<list>
#include<string>
#include<algorithm>

using namespace std;

class Driver
{
protected:
	int mVehicleNo;
	string mName;
	string mOrigin;
	string mDestination;
	int mStartTime;
	int mDuration;


public:

	vector<int> customerIds;

	Driver()
	{


	}

	Driver(int vehicleNo, string name)
	{
		this->mVehicleNo = vehicleNo;
		this->mName = name;
	}

	int getVehicleNo()
	{
		return mVehicleNo;
	}

	void setVehicleNo(int vehicleNo)
	{
		mVehicleNo = vehicleNo;
	}


	string getName()
	{
		return mName;
	}

	void setName(string name)
	{
		mName = name;
	}


	string getOrigin()
	{
		return mOrigin;
	}

	void setOrigin(string origin)
	{
		mOrigin = origin;
	}


	string getDestination()
	{
		return mDestination;
	}

	void setDestination(string destination)
	{
		mDestination = destination;
	}



	int getStartTime()
	{
		return mStartTime;
	}

	void setStartTime(int startTime)
	{
		mStartTime = startTime;
	}



	int getDuration()
	{
		return mDuration;
	}

	void setDuration(int duration)
	{
		mDuration = duration;
	}

};


class Rider
{
public:
	int mId;
	string mName;
	string mOrigin;
	string mDestination;

};

//vid, object
map<int, Driver> driverInventory;
map<int, Rider> riderInventory;

//cId, vId
map<int, int> customerMapping;

//origin + destin, vId
map<string, list<int> >  ridesInventory;




bool compareBasedOnFastest(int v1, int v2)
{
	Driver &d1 = driverInventory[v1];
	Driver &d2 = driverInventory[v2];

	if (d1.getDuration() < d2.getDuration())
		return true;

	return false;

}


bool compareBasedOnShortest(int v1, int v2)
{
	Driver &d1 = driverInventory[v1];
	Driver &d2 = driverInventory[v2];

	if (d1.getDuration() + d1.getStartTime() < d2.getDuration() + d2.getStartTime())
		return true;

	return false;
}


void removeDriverFromList(string key, int vehicleNo, int userId)
{

	if (driverInventory[vehicleNo].customerIds.size() >= 3)
	{
		list<int> &rList = ridesInventory[key];
		rList.remove(vehicleNo);
	}

	else
	{
		driverInventory[vehicleNo].customerIds.push_back(userId);
	}
}




void offerRide(int vehicleNo, string name, string origin, string destination, int startTime, int duration)
{
	if (driverInventory.find(vehicleNo) == driverInventory.end())
	{
		Driver d(vehicleNo, name);
		driverInventory[vehicleNo] = d;
	}

	Driver &rTemp = driverInventory[vehicleNo];

	string key = rTemp.getOrigin();
	key += rTemp.getDestination();
	list<int> &rList = ridesInventory[key];
	rList.remove(vehicleNo);


	rTemp.setOrigin(origin);
	rTemp.setDestination(destination);
	rTemp.setStartTime(startTime);
	rTemp.setDuration(duration);
	rTemp.customerIds.clear();

	ridesInventory[origin + destination].push_back(vehicleNo);

}



void selectRide(int userId, string origin, string destination, string parameter)
{
	string key = origin + destination;
	list<int> &rList = ridesInventory[key];

	if (parameter == "fastest")
		rList.sort(compareBasedOnFastest);

	else
		rList.sort(compareBasedOnShortest);

	int vehicleNo = rList.front();
	removeDriverFromList(key, vehicleNo, userId);

	customerMapping[userId] = vehicleNo;

}

void displayInventory()
{
	map<int, Driver>::iterator it;

	for (it = driverInventory.begin(); it != driverInventory.end(); ++it)
	{
		cout << it->first << (it->second).getName() << " " << (it->second).getStartTime() << "  " << (it->second).getDuration() << endl;
	}

}


void displayMapping()
{
	cout << "Cutomer-DriverMapping : " << endl;
	map<int, int> ::iterator it;

	for (it = customerMapping.begin(); it != customerMapping.end(); ++it)
	{
		cout << "CustomerId: " << it->first << "   ";
		cout << "VehicleNo :" << it->second << endl;
	}
}


void displayDrivers()
{
	map<string, list<int>>::iterator it;

	for (it = ridesInventory.begin(); it != ridesInventory.end(); ++it)
	{
		cout << it->first << "   " << endl;
		list<int> &temp = it->second;

		list<int>::iterator it_l;

		for (it_l = temp.begin(); it_l != temp.end(); ++it_l)
		{
			Driver &d = driverInventory[*it_l];
			cout << "Name :" << d.getName() + "  " << "No. :" << d.getVehicleNo() << "  " << "start time:  " << d.getStartTime() << "  " << d.getDuration() << endl;
		}

		cout << endl << endl << endl;

	}

}





int main()
{

	//offerRide(int vehicleNo, string name, string origin, string destination, int startTime, int duration)
	offerRide(1001, "John", "BLR", "DEL", 1100, 200);
	offerRide(1002, "Sam", "HYD", "MAA", 1500, 100);
	offerRide(1003, "Chris", "JFK", "LAX", 1400, 500);
	offerRide(1001, "John", "DEL", "HYD", 1700, 200);
	offerRide(1005, "Christina", "JFK", "LAX", 1350, 300);
	offerRide(1009, "Sameer", "HYD", "MAA", 1500, 200);
	offerRide(1011, "Samuel", "HYD", "MAA", 1200, 300);


	selectRide(001, "HYD", "MAA", "fastest");
	selectRide(002, "HYD", "MAA", "fastest");
	displayDrivers();

	selectRide(002, "JFK", "LAX", "shortest");
	selectRide(001, "HYD", "MAA", "shortest");

	displayMapping();
	displayDrivers();

	system("pause");
	return 0;
} '''
