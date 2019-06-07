#include <iostream>
#include <thread>
#include "count.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "hello!" << endl;

	Count* pCount = new Count(500);

	thread* pthCount = new thread(&Count::Run, pCount);
	pCount->Start();

	while (true)
	{
		unsigned long int N = pCount->getCountNum();
		cout << "The Count Num: " << N << endl;
		if (N == 20) {
			pCount->setStop();
		}
		if (pCount->isStoped()) {
			break;
		}
		Sleep(100);
	}
	cout << "Function done!" << endl;
	system("pause");
	return 0;
}
