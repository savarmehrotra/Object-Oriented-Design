#include<bits/stdc++.h>

using namespace std;

int M;
int N;


enum users{User, Admin, Root};
users types[3] = { User, Admin, Root };



class Job
{
public:

	Job(int id, int duration, int priority, int deadline, users user)
	{
		mJobId = id;
		mDuration = duration;
		mPriority = priority;
		mDeadline = deadline;
		mUser = user;
	}


	int mJobId;
	int mDuration;
	int mPriority;
	int mDeadline;
	users mUser;
};



void display(vector< queue<int> > threadPool)
{
	for (int i = 0; i < threadPool.size(); ++i)
	{
		cout <<endl << "Thread " + to_string(i + 1) + ": " ;

		 while( threadPool[i].size() != 0 )
		{
			 cout << threadPool[i].front() << ",";
			 threadPool[i].pop();
		}
		 cout << endl;
	}
}


class Compare
{
public:
	bool operator() (pair<int, int> p1, pair<int, int> p2)
	{
		if(p1.second > p2.second)
			return true;

		return false;
	}
};




bool compare_sjfs(Job * j1, Job * j2)
{
	if (j1->mDuration < j2->mDuration)
	{
		return true;
	}

	else if (j1->mDuration == j2->mDuration && j1->mPriority > j2->mPriority)
	{
		return true;
	}

	return false;
}




bool compare_fps(Job * j1, Job * j2)
{
	if (j1->mPriority > j2->mPriority)
	{
		return true;
	}

	else if (j1->mPriority == j2->mPriority && j1->mUser > j2->mUser)
	{
		return true;
	}


	else if (j1->mPriority == j2->mPriority && j1->mUser == j2->mUser && j1->mDuration > j2->mDuration)
	{
		return true;
	}

	return false;
}




bool compare_edf(Job * j1, Job * j2)
{
	if (j1->mDeadline < j2->mDeadline)
	{
		return true;
	}

	else if (j1->mDeadline == j2->mDeadline && j1->mPriority > j2->mPriority)
	{
		return true;
	}

	else if (j1->mDeadline == j2->mDeadline && j1->mPriority == j2->mPriority && j1->mDuration < j2->mDuration)
	{
		return true;
	}

	return false;
}




void fcfs(vector<Job *> jobQueue)
{
	vector< queue<int> > threadPool(M);
	
	
	// id, time

	priority_queue< pair<int, int>, vector<pair<int, int> >, Compare > threadTime;

	for (int i = 0; i < M; ++i)
	{
		threadTime.push( make_pair(i, 0) );
	}


	for (int i = 0; i < N; ++i)
	{
		Job *pTemp = jobQueue[0];
		jobQueue.erase(jobQueue.begin() );

		int thread_no = threadTime.top().first; 
		int thread_time_sum = threadTime.top().second;
		threadTime.pop();

		if (pTemp->mDeadline - pTemp->mDuration >= thread_time_sum)
		{
			threadPool[thread_no].push(pTemp->mJobId);
			
			thread_time_sum += pTemp->mDuration;
			
		}

		threadTime.push(make_pair(thread_no, thread_time_sum));
		
	}

	display(threadPool);
}





void sjfs(vector<Job *> jobQueue)
{

	vector< queue<int> > threadPool(M);
	//id , time
	priority_queue< pair<int, int>, vector<pair<int, int> >, Compare > threadTime;

	for (int i = 0; i < M; ++i)
	{
		threadTime.push(make_pair(i, 0));
	}


	sort(jobQueue.begin(), jobQueue.end(), compare_sjfs );


	for (int i = 0; i < N; ++i)
	{
		Job *pTemp = jobQueue[0];
		jobQueue.erase(jobQueue.begin());

		int thread_no = threadTime.top().first;
		int thread_time_sum = threadTime.top().second;
		threadTime.pop();

		if (pTemp->mDeadline - pTemp->mDuration >= thread_time_sum)
		{
			threadPool[thread_no].push(pTemp->mJobId);

			thread_time_sum += pTemp->mDuration;

		}

		threadTime.push(make_pair(thread_no, thread_time_sum));

	}

	display(threadPool);
}



void fps(vector<Job *> jobQueue)
{

	vector< queue<int> > threadPool(M);
	//id , time
	priority_queue< pair<int, int>, vector<pair<int, int> >, Compare > threadTime;

	for (int i = 0; i < M; ++i)
	{
		threadTime.push(make_pair(i, 0));
	}


	sort(jobQueue.begin(), jobQueue.end(), compare_fps);

	for (int i = 0; i < N; ++i)
	{
		Job *pTemp = jobQueue[0];
		jobQueue.erase(jobQueue.begin());

		int thread_no = threadTime.top().first;
		int thread_time_sum = threadTime.top().second;
		threadTime.pop();

		if (pTemp->mDeadline - pTemp->mDuration >= thread_time_sum)
		{
			threadPool[thread_no].push(pTemp->mJobId);

			thread_time_sum += pTemp->mDuration;

		}

		threadTime.push(make_pair(thread_no, thread_time_sum));

	}

	display(threadPool);
}




void edf(vector<Job *> jobQueue)
{

	vector< queue<int> > threadPool(M);
	
	//id , time
	priority_queue< pair<int, int>, vector<pair<int, int> >, Compare > threadTime;

	for (int i = 0; i < M; ++i)
	{
		threadTime.push(make_pair(i, 0));
	}


	sort(jobQueue.begin(), jobQueue.end(), compare_edf);


	for (int i = 0; i < N; ++i)
	{
		Job *pTemp = jobQueue[0];
		jobQueue.erase(jobQueue.begin());

		int thread_no = threadTime.top().first;
		int thread_time_sum = threadTime.top().second;
		threadTime.pop();

		if (pTemp->mDeadline - pTemp->mDuration >= thread_time_sum)
		{
			threadPool[thread_no].push(pTemp->mJobId);

			thread_time_sum += pTemp->mDuration;

		}

		threadTime.push(make_pair(thread_no, thread_time_sum));

	}


	display(threadPool);
}




int main()
{
	cin >> N >> M;
	vector<Job *> jobQueue;


	for (int i = 0; i < N; ++i)
	{
		int id, duration, priority, deadline; 
		int i_user;
		
		cin >> id >> duration >> priority >> deadline>> i_user;
		
		try
		{
			if (i_user >= 3)
				throw 2;
		}

		catch(int val)
		{
			i_user = val;
		}


		Job * pTemp = new Job(id, duration, priority, deadline, types[i_user] );
		
		jobQueue.push_back(pTemp);

	}
	
	cout << "FCFS :";
	fcfs(jobQueue);
	cout<< endl << endl;

	cout << "SJFS :";
	sjfs(jobQueue);
	cout << endl << endl;

	cout << "FPS :";
	fps(jobQueue);
	cout << endl << endl;

	cout << "EDF :";
	edf(jobQueue);
	cout << endl << endl;


	system("pause");

	return 0;
}