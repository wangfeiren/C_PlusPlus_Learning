#include "count.h"

Count::Count(unsigned int time) :mTime(time)
{
	cout << "Count time was set as: " << time << " ms." << endl;
}

void Count::Run()
{
	while (true)
	{
		if (isToStop()) {
			break;
		}
		if (mbStart) {
			N++;
			Sleep(mTime);
		}
		else {
			Sleep(2);
		}
	}
	setStoped();
}

unsigned long int Count::getCountNum()
{
	unique_lock<mutex> lock(mMutexN);
	return N;
}

void Count::Reset()
{
	N = 0;
	{
		unique_lock<mutex> lock(mMutexStart);
		mbStart = false;
	}
}

void Count::Start()
{
	unique_lock<mutex> lock(mMutexStart);
	mbStart = true;
}

void Count::Pause()
{
	unique_lock<mutex> lock(mMutexStart);
	mbStart = false;
}

void Count::setStop()
{
	unique_lock<mutex> lock(mMutexStop);
	mbStop = true;
}

bool Count::isToStop()
{
	unique_lock<mutex> lock(mMutexStop);
	return mbStop;
}

void Count::setStoped()
{
	unique_lock<mutex> lock(mMutexStoped);
	mbStoped = true;
}

bool Count::isStoped()
{
	unique_lock<mutex> lock(mMutexStoped);
	return mbStoped;
}
