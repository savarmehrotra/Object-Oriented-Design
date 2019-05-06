#include<bits/stdc++.h>

using namespace std;


class Vehicle
{
protected:
	string mType;
	bool mAvailable;
	map<string, int> mSlotPrice;


public:
	int id;
	virtual string getType() = 0;
	virtual bool isAvailable() = 0;
	virtual int getSlotPrice(string slot) = 0;
	virtual void setAsNotAvailable() = 0;
	virtual void setAsAvailable() = 0;
	virtual int getId() = 0;
};


class Bike : public Vehicle
{

public:

	Bike(map<string, int> price)
	{
		mAvailable = true;
		mSlotPrice = price;

	}

	string getType()
	{
		return this->mType;
	}

	bool isAvailable()
	{
		return this->mAvailable;
	}

	int getSlotPrice(string slot)
	{
		return this->mSlotPrice[slot];
	}

	void setAsNotAvailable()
	{
		this->mAvailable = false;
	}

	void setAsAvailable()
	{
		this->mAvailable = true;
	}

	int getId()
	{
		return id;
	}


};


class Car : public Vehicle
{

public:

	Car(map<string, int> price)
	{
		mAvailable = true;
		mSlotPrice = price;

	}
	string getType()
	{
		return this->mType;
	}

	bool isAvailable()
	{
		return this->mAvailable;
	}

	int getSlotPrice(string slot)
	{
		return this->mSlotPrice[slot];
	}

	void setAsNotAvailable()
	{
		this->mAvailable = false;
	}

	void setAsAvailable()
	{
		this->mAvailable = true;
	}

	int getId()
	{
		return id;
	}
};



class Truck : public Vehicle
{

public:

	Truck(map<string, int> price)
	{
		mAvailable = true;
		mSlotPrice = price;
	}

	string getType()
	{
		return this->mType;
	}

	bool isAvailable()
	{
		return this->mAvailable;
	}

	int getSlotPrice(string slot)
	{
		return this->mSlotPrice[slot];
	}

	void setAsNotAvailable()
	{
		this->mAvailable = false;
	}


	void setAsAvailable()
	{
		this->mAvailable = true;
	}

	int getId()
	{
		return id;
	}
};



struct Result
{
	int id;
	string timeSlot;
	string type;
	int price;

};



bool compa(Result v1, Result v2)
{

	if (v1.price < v2.price )
		return true;

	return false;

}



vector<Result> searchForVehicle(string timeSlot, string type, string userPrice, map<string, list<Vehicle *> >  &inventory, bool sortedList)
{
	vector<Result> vehicle_list;

	int price;

	if ( userPrice.empty() )
		price = INT_MAX;

	else
		price = stoi(userPrice);

	try
	{
		if (price < 0)
			throw "Invalid Price";
	}

	catch (const char * s)
	{
		cout << "Invlaid Price Entered";
	}

		map < string, list<Vehicle *> >::iterator it1;

		for (it1 = inventory.begin(); it1 != inventory.end(); ++it1)
		{
			list<Vehicle *>::iterator it2;

			for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2)
			{
				if (
					((*it2)->isAvailable() == false) ||
					((*it2)->getSlotPrice(it1->first) > price) ||
					(!type.empty() && (*it2)->getType() != type)
					)

				{
					continue;
				}

				Result * temp = new Result;
				temp->id = (*it2)->getId();
				temp->timeSlot = it1->first;
				temp->type = (*it2)->getType();
				temp->price = (*it2)->getSlotPrice(it1->first);

				vehicle_list.push_back(*temp);
			}
		}

		if (sortedList)
			sort(vehicle_list.begin(), vehicle_list.end(), compa);

		return vehicle_list;

	}




	void bookVehicle( string timeSlot, string type, string userPrice, map < string, list<Vehicle *> >  &inventory)
	{

		try
		{
			if ( timeSlot.size() == 0 )
			{
				throw "Time Slot Not Entered";
			}
		}

		catch(const char * c)
		{
			cout << "Invalid Time Slot";
		}


		list<Vehicle *>::iterator it;

		for ( it = inventory[timeSlot].begin(); it != inventory[timeSlot].end(); it++)
		{
			if ( (*it)->isAvailable() && (*it)->getType() == type)
			{
				(*it)->setAsNotAvailable();
			}
		}

	}


	class VehicleFactory
	{
		static Vehicle * createNewVehicle(int id, string type, map<string, int> slotPrices, map < string, list<Vehicle *> >  &inventory)
		{
			Vehicle * v;

			if (type == "CAR")
			{
				v = new Car(slotPrices);
			}

			if (type == "TRUCK")
			{
				v = new Truck(slotPrices);
			}


			if (type == "BIKE")
			{
				v = new Bike(slotPrices);
			}

			return v;

		}
	};



	int main()
	{
		map < string, list<Vehicle *> >  inventory;

		Vehicle * v;

		inventory["MORNING"].push_back(v);
		inventory["EVENING"].push_back(v);
		inventory["NIGHT"].push_back(v);
		inventory["AFTERNOON"].push_back(v);


		return 0;
	}


































	//All
	/*if (timeSlot.empty() && type.empty() && userPrice.empty())
	{
	map < string, list<Vehicle *> >::iterator it1;

	for (it1 = inventory.begin(); it1 != inventory.end(); ++it1)
	{
	list<Vehicle *>::iterator it2;

	for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2)
	{
	if ((*it2)->isAvailable() == false)
	continue;

	Result temp;
	temp.timeSlot = it1->first;
	temp.type = (*it2)->getType();
	temp.type = (*it2)->getSlotPrice(it1->first);
	vehicle_list.push_back(temp);
	}
	}


	if(sortedList)
	sort(vehicle_list.begin(), vehicle_list.end(), compa);

	return vehicle_list;
	} */








	/**
	//Only time slot
	else if (!timeSlot.empty() && type.empty() && userPrice.empty())
	{
	list<Vehicle>::iterator it;

	for (it = inventory[timeSlot].begin() ; it != inventory[timeSlot].end(); ++it)
	{
	if ( (*it).isAvailable == false)
	continue;

	Result temp;
	temp.timeSlot = timeSlot;
	temp.type = (*it).getType();
	temp.type = (*it).getSlotPrice(timeSlot);
	vehicle_list.push_back(temp);
	}

	return vehicle_list;
	}

	//Only type
	else if (timeSlot.empty() && !type.empty() && userPrice.empty() )
	{
	map < string, list<Vehicle> >::iterator it1;

	for (it1 = inventory.begin(); it1 != inventory.end(); ++it1)
	{
	list<Vehicle>::iterator it2;

	for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2)
	{
	if ((*it2).isAvailable == false || (*it2).getType() != type)
	continue;

	Result temp;
	temp.timeSlot = it1->first;
	temp.type = (*it2).getType();
	temp.type = (*it2).getSlotPrice(it1->first);
	vehicle_list.push_back(temp);
	}
	}

	return vehicle_list;
	}


	//Only price
	else if (timeSlot.empty() && type.empty() && !userPrice.empty() )
	{
	map < string, list<Vehicle> >::iterator it1;

	for (it1 = inventory.begin(); it1 != inventory.end(); ++it1)
	{
	list<Vehicle>::iterator it2;

	for (it2 = (*it1).second.begin(); it2 != (*it1).second.end(); ++it2)
	{
	if ( (*it2).isAvailable == false || (*it2).getSlotPrice(it1->first) > price)
	continue;

	Result temp;
	temp.timeSlot = it1->first;
	temp.type = (*it2).getType();
	temp.type = (*it2).getSlotPrice(it1->first);
	vehicle_list.push_back(temp);
	}
	}

	return vehicle_list;
	} */


	//All Others
