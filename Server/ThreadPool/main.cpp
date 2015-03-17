#include <stdio.h>
#include <stdlib.h>
#include "ThreadPool.h"

class user {
	// Simple Work Function
public:
	DWORD is_prime2(int x)
	{
		Sleep(1000);
		bool res = false;
		//printf("Calculating. Please, wait...\n");
		for (int i = 2; i < x; ++i) if (x%i == 0) res = false;
		res = true;
		if (res)
			printf("%d: %d is prime\n", GetCurrentThreadId(), x);
		else
			printf("%d: %d is not prime\n", GetCurrentThreadId(), x);
		return x;
	}
};

int main(int argc, char* argv[])
{
	user u;
	_ThreadPool *gThreadPool = new _ThreadPool;
	initThreadPool(gThreadPool);
	MakeThreadToPool(gThreadPool, 3);
	//DoTimer(20000, gThreadPool, &user::is_prime2, u, 1000, 1200);
	//DoTimer(11000, gThreadPool, &user::is_prime2, u, 2500, 2000);
	for (int i = 0; i < 10; i++)
	{
		DoAsync(gThreadPool, &user::is_prime2, u, i);
	}
	Sleep(5000);
	for (int i = 0; i < 10; i++)
	{
		DoAsync(gThreadPool, &user::is_prime2, u, i);
	}
	Sleep(50000);  // main 쓰레드가 먼저 소멸되는 현상을 방지하기 위해

	return 0;
}