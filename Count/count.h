#ifndef COUNT_H_
#define COUNT_H_

#include <iostream>
#include <mutex>
#include <Windows.h>

using namespace std;

class Count {
public:
	Count(unsigned int time);
	void setStop();
	bool isStoped();
	void Run();
	void Reset();
	void Start();
	void Pause();
	unsigned long int getCountNum();
private:
	bool isToStop();
	void setStoped();
private:
	unsigned long int N = 0;
	unsigned int mTime;
	std::mutex mMutexStop;
	std::mutex mMutexStoped;
	std::mutex mMutexN;
	std::mutex mMutexStart;
	bool mbStop = false;
	bool mbStoped = false;
	bool mbStart = false;
};

#endif // !COUNT_H_

