#include <stdio.h>
#include <stdlib.h>
#include "ThreadPool.h"

// Simple Work Function
DWORD is_prime(int x)
{
	Sleep(1000);
	bool res=false;
	//printf("Calculating. Please, wait...\n");
	for (int i = 2; i<x; ++i) if (x%i == 0) res=false;
	res=true;
	if (res)
		printf("%d: %d is prime\n", GetCurrentThreadId(), x);
	else
		printf("%d: %d is not prime\n", GetCurrentThreadId(), x);
	return x;
}

int main(int argc, char* argv[])
{
	_ThreadPool *gThreadPool = new _ThreadPool;
	initThreadPool(gThreadPool);
	MakeThreadToPool(gThreadPool, 3);
	for (int i = 0; i < 100; i++)
		asyncWork(gThreadPool, (WORK)is_prime, (LPVOID)i);	
	Sleep(50000);  // main 쓰레드가 먼저 소멸되는 현상을 방지하기 위해

	return 0;
}