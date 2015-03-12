#include <stdio.h>
#include <stdlib.h>
#include "ThreadPool.h"

class user {
	// Simple Work Function
public:
	DWORD is_prime2(int x, int y)
	{
		Sleep(1000);
		bool res = false;
		//printf("Calculating. Please, wait...\n");
		for (int i = 2; i < x; ++i) if (x%i == 0) res = false;
		res = true;
		if (res)
			printf("%d: %d is prime\n", GetCurrentThreadId(), x+y);
		else
			printf("%d: %d is not prime\n", GetCurrentThreadId(), x+y);
		return x;
	}
};

int main(int argc, char* argv[])
{
	user u;
	_ThreadPool *gThreadPool = new _ThreadPool;
	initThreadPool(gThreadPool);
	MakeThreadToPool(gThreadPool, 3);

	//======
	function<DWORD()> fuc = bind(&user::is_prime2, &u, 2, 3);
	auto asyncWork = bind(AddWorkToPool, _1, fuc);
	//======
	//auto asyncWork = asyncWorkInit(gThreadPool, u, &user::is_prime2);
	for (int i = 0; i < 21; i++)
		asyncWork(gThreadPool);		
	Sleep(50000);  // main 쓰레드가 먼저 소멸되는 현상을 방지하기 위해

	return 0;
}