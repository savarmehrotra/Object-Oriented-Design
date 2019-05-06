#include<bits/stdc++.h>

using namespace std;

enum employee_types{worker, manager, ceo};

class Employee;

class Employee
{
public:
	
	int mId;
	employee_types mType;
	string mName;
	int mManagerId;
	int mSalary;
	int mRating;
	int mBonus;
	vector<Employee *> mJuniors;

	Employee()
	{

	}

	Employee(int id, employee_types type, string name, int managerId, int salary, int rating)
	{
		mId = id;
		mType = type;
		mName = name;
		mManagerId = managerId;
		mSalary = salary;
		mRating = rating;
		mBonus;
		vector<Employee *> * t = new vector<Employee *>();
		mJuniors = *t;
		
	}

	
};


int ratingSum = 0;

map<int, Employee *> empMap;


class Org
{
public:
	
	Employee * mCEO;

	Org(string name, int salary, int rating)
	{
		Employee * pTemp = new Employee(001, ceo, name, 000, salary, rating);
		mCEO = pTemp;
		empMap[001] = mCEO;
	}

	void addEmployee(int id, employee_types type, string name, int managerId, int salary, int rating)
	{
		ratingSum += rating;

		Employee * pTemp = new Employee(id, type, name, managerId, salary, rating);
		
		if ( empMap.find(id) != empMap.end() )
		{
			pTemp->mJuniors =  empMap[id]->mJuniors;
		}
		
		empMap[id] = pTemp;


		if ( empMap.find(managerId) == empMap.end() )
		{
			addEmployee(managerId, manager, "", 001, 0, 0);
		}

		//cout << empMap.begin()->first << endl;


		Employee * t = empMap[managerId];
		
		//cout << t->mJuniors.size() << endl;
		t->mJuniors.push_back(pTemp);
	}

	void printJuniors(int id)
	{
		Employee *pEmp = empMap[id];

		if (pEmp != NULL)
		{
			cout << pEmp->mId << pEmp->mName << " ";
			cout << endl;

			for (int i = 0; i < pEmp->mJuniors.size(); ++i)
			{
				printJuniors(pEmp->mJuniors[i]->mId);
			}
		}
	}


	void allocateBonus(int bonusAmount, Employee *pCurr)
	{
		pCurr->mBonus = bonusAmount * (pCurr->mRating / ratingSum);
		
		for (int i = 0; i < pCurr->mJuniors.size(); ++i)
		{
			allocateBonus(bonusAmount, pCurr->mJuniors[i]);
		}
	}

	class Compare
	{
	public:
		bool operator() (pair<int, int> p1, pair<int, int> p2)
		{
			if(p1.second < p2.second)
				return true;

			return false;

		}
	};

	void foo(Employee * pCurr, priority_queue< pair <int, int>, vector<pair<int, int>>, Compare> &maxHeap)
	{
		if (pCurr == NULL)
			return;

		maxHeap.push( make_pair(pCurr->mId, pCurr->mSalary) );

		for (int i = 0; i < pCurr->mJuniors.size(); ++i)
		{
			foo(pCurr->mJuniors[i], maxHeap);
		}
	}



	void topTen()
	{
		priority_queue< pair <int, int> , vector<pair<int, int>>, Compare> maxHeap;

		foo(mCEO, maxHeap);

		for (int i = 0; !maxHeap.empty() && i < 10; ++i)
		{
			cout << maxHeap.top().first << " : "<< maxHeap.top().second<<" ";
			maxHeap.pop();
		}
	}


};







int main()
{
	Org org("Zuck", 10000, 1);

	org.addEmployee(002, manager, "Theil", 001, 9000, 2);
	org.addEmployee(003, manager, "Dustin", 001, 9000, 2);
	
	org.addEmployee(004, worker, "w1",  002, 8000, 4);
	org.addEmployee(005, worker, "w3",  002, 7000, 2);
	org.addEmployee(006, manager, "w4", 003, 4000, 2);
	org.addEmployee(007, manager, "w5", 003, 5000, 2);
	//org.addEmployee(009, manager, "w6", 002, 9000, 2);
	

	map<int, Employee *>::iterator it;

	for (it = empMap.begin(); it != empMap.end(); ++it)
	{
		cout << it->first << "  "<< it->second->mName << endl;
	}

	cout << endl << endl;
	org.printJuniors(1);
	
	org.topTen();
	system("pause");
	return 0;
}



