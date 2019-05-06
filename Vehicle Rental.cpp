#include<bits/stdc++.h>

using namespace std;



class Vehicle
{
protected:
	int mId;
	string mType;
	int mEveningPrice;
	int mMorningPrice;
	int mAfternoonPrice;
	int mNightPrice;

public:
	void setId(int id)
	{
		mId = id;
	}

	int getId()
	{
		return mId;
	}

	void setType(string type)
	{
		mType = type;

	}

	string getType()
	{
		return mType;
	}


	void setMorningPrice(int price)
	{
		mMorningPrice = price;
	}


	int getMorningPrice()
	{
		return mMorningPrice;
	}


	void setAfterNoonPrice(int price)
	{
		mAfternoonPrice = price;
	}

	int getAfterNoonPrice()
	{
		return mAfternoonPrice;
	}

	void setEveningPrice(int price)
	{
		mEveningPrice = price;
	}

	
	int getEveningPrice()
	{
		return mEveningPrice;
	}
	

	void setNighPrice(int price)
	{
		mNightPrice = price;
	}

	int getnightPrice()
	{
		return mNightPrice;
	}


};




map<int, Vehicle> VehicleInventory;
//map<int, Car> CarInventory;
//map<int, Truck> TruckInventory;

map<int, bool > MorningSlot;
map <int, bool> AfterNoonSlot;
map<int, bool>EveningSlot;
map<int, bool>NightSlot;

//map<int, pair<bool, int> >EveningSlot;
//map<int, pair<bool, int> >NightSlot;




void cancelBooking(string slot, int id)
{
	try
	{
		if (slot.empty() || id < 0)
			throw "invalid input";
	}

	catch (const char * c)
	{
		cout << c << endl;
	}


	if (slot == "Morning")
		MorningSlot[id] = true;

	else if (slot == "Afternoon")
		AfterNoonSlot[id] = true;

	else if (slot == "Night")
		NightSlot[id] = true;

	else if (slot == "Evening")
		EveningSlot[id] = true;

	else
		cout << "Invalid input";

	return;
}


void makeBooking(string slot, int id)
{
	try
	{
		if (slot.empty() || id < 0)
			throw "invalid input";
	}
	catch (const char * c)
	{
		cout << c << endl;
	}


	if (slot == "Morning")
		MorningSlot[id] = false;

	else if (slot == "Afternoon")
		AfterNoonSlot[id] = false;

	else if (slot == "Night")
		NightSlot[id] = false;

	else if (slot == "Evening")
		EveningSlot[id] = false;

	else
		cout << "Invalid input";



	return;
}//handle invalid id, type



struct Result
{
	string type;
	int price;
};


bool compare(Result r1, Result r2)
{
	if (r1.price < r2.price)
		return true;

	return false;
}


vector<Result> search(string slot, string type, int price, bool sorted)
{
	if (price == 0)
		price = INT_MAX;

	vector<Result> ans;


	if (slot.empty() || slot == "Morning")
	{
		map<int, bool>::iterator it;

		for (it = MorningSlot.begin(); it != MorningSlot.end(); ++it)
		{
			Vehicle rv = VehicleInventory[it->first];

			if ( (!type.empty() && rv.getType() != type) || rv.getMorningPrice() > price || !it->second )
				continue;

			else
			{
				Result temp;
				temp.type = rv.getType();
				temp.price = rv.getMorningPrice();
				ans.push_back(temp);
			}
		}
	}


	if (slot.empty() || slot == "Afternoon")
	{
		map<int, bool>::iterator it;

		for (it = AfterNoonSlot.begin(); it != AfterNoonSlot.end(); ++it)
		{
			Vehicle &rv = VehicleInventory[it->first];

			if ( (!type.empty() && rv.getType() != type) || rv.getAfterNoonPrice() > price || !it->second)
				continue;

			else
			{
				Result temp;
				temp.type = rv.getType();
				temp.price = rv.getMorningPrice();
				ans.push_back(temp);
			}
		}
	}


	if (slot.empty() || slot == "Evening")
	{
		map<int, bool>::iterator it;

		for (it = EveningSlot.begin(); it != EveningSlot.end(); ++it)
		{
			Vehicle &rv = VehicleInventory[it->first];

			if ((!type.empty() && rv.getType() != type) || rv.getEveningPrice() > price || !it->second)
				continue;

			else
			{
				Result temp;
				temp.type = rv.getType();
				temp.price = rv.getEveningPrice();
				ans.push_back(temp);
			}
		}
	}


	if (slot.empty() || slot == "Night")
	{
		map<int, bool>::iterator it;

		for (it = NightSlot.begin(); it != NightSlot.end(); ++it)
		{
			Vehicle &rv = VehicleInventory[it->first];

			if ((!type.empty() && rv.getType() != type) || rv.getnightPrice() > price || !it->second)
				continue;

			else
			{
				Result temp;
				temp.type = rv.getType();
				temp.price = rv.getMorningPrice();
				ans.push_back(temp);
			}
		}
	}




		if(sorted)
			sort(ans.begin(), ans.end(), compare);

		return ans;
}



void display(vector<Result> A)
{
	for (int i = 0; i < A.size(); ++i)
		cout << A[i].type << " " << A[i].price << endl;

	cout << endl << endl << endl;
}



int main()
{
	vector<string> TYPES;
	TYPES.push_back("Car");
	TYPES.push_back("Truck");
	TYPES.push_back("Bike");
	srand(0);

	for (int i = 1; i <= 10; ++i)
	{
		Vehicle v1;
		v1.setId(i);
		v1.setType( TYPES[ rand() % 3 ] );
		v1.setMorningPrice( (rand() % 1000) + 1000);
		v1.setAfterNoonPrice( (rand() % 1000) + 1500);
		v1.setEveningPrice( (rand() % 1000) + 2000);
		v1.setNighPrice( (rand() % 1000) + 2500);
		VehicleInventory[i] = v1;
		MorningSlot[i] = true;
		AfterNoonSlot[i] = true;
		EveningSlot[i] = true;
		NightSlot[i] = true;
	}


	map<int, Vehicle>::iterator it;
	cout<<"Displaying the Vehicle Inventory : "<<endl<<endl;

	for (it = VehicleInventory.begin(); it != VehicleInventory.end(); ++it)
	{
	
		cout << it->second.getId() << " ";
		cout << it->second.getType() << " ";
		cout << it->second.getMorningPrice() << " " ;
		cout << it->second.getAfterNoonPrice() << " ";
		cout << it->second.getEveningPrice() << " ";
		cout << it->second.getnightPrice() << " ";
		cout << endl <<endl;
	}



	makeBooking("Morning", 5);
	makeBooking("Afternoon", 5);
	makeBooking("Evening", 5);
	display(search("Evening", "Car", 5000, true));

	cancelBooking("Evening", 5);

	display( search("Evening", "Car", 5000, true) ); 


	makeBooking("Night", 4);
	makeBooking("Night", 9);

	display( search("", "Car", 2000, false) );



	system("pause");
	return 0;
}




/**
class Bike : public Vehicle
{

};

class Car : public Vehicle
{

};


class Truck :public Vehicle
{

}; */