#include "MemoryPool.h"
#include <cstring>
#include <cassert>

MemoryPool::MemoryPool() {
	mMap.clear();
	for (int i = 0; i < nPoolSize; i++)
	{
		makeBlock(i, nLength[i]);
		InitializeCriticalSection(&cs[i]);
	}
}

template <typename T>
T* MemoryPool::malloc(const int count)
{
	int nIndex = getIndex(sizeof(T)* count);

	if (nIndex < nPoolSize)
	{
		// lock
		EnterCriticalSection(&mPool->cs[nIndex]);

		// 현재 사용 가능한 메모리 블록이 없는경우, 추가량만큼 할당을 해준다.
		if (mPool->memory[nIndex].empty())
		{
			mPool->makeBlock(nIndex, nLength[nIndex]);
		}

		BIT_8* mBlock = mPool->memory[nIndex].top();
		mPool->memory[nIndex].pop();
		LeaveCriticalSection(&mPool->cs[nIndex]);
		// unlock


		for (int i = 0; i < count; i++)
		{
			T* pObject = (T *)(mBlock + i*sizeof(T));
			new (pObject)T();	// call default - constructor
		}

		return (T*)mBlock;
	}
	else
	{
		// 엄청 큰거라면, OS에서 할당하는 것이 이득
		// 이렇게까지 큰 객체는, 생성자와 소멸자를 따로 불러주지 않는다. (소멸자에서 처리 방법이 떠오르지 않음 TT)
		return (T*)malloc(sizeof(T)* count);
	}
}

int MemoryPool::getIndex(int nSize)
{
	int nIndex = 0;
	while (nIndex < nPoolSize)
	{
		if (nSize <= nLength[nIndex])
		{
			break;
		}
		nIndex++;
	}

	return nIndex;
}

void* MemoryPool::malloc(std::size_t size)
{
	int nIndex = getIndex(size);

	if (nIndex < nPoolSize)
	{
		// lock
		EnterCriticalSection(&mPool->cs[nIndex]);

		// 현재 사용 가능한 메모리 블록이 없는경우, 추가량만큼 할당을 해준다.
		if (mPool->memory[nIndex].empty())
		{
			mPool->makeBlock(nIndex, nLength[nIndex]);
		}

		void* mBlock = mPool->memory[nIndex].top();
		mPool->memory[nIndex].pop();
		LeaveCriticalSection(&mPool->cs[nIndex]);
		// unlock

		memset(mBlock, 0, nLength[nIndex]);

		return mBlock;
	}
	else
	{
		// 엄청 큰거라면, OS에서 할당하는 것이 이득
		BIT_8* alloc = new BIT_8[size];
		mPool->mMap[alloc] = nPoolSize;
		return alloc;
	}
}

void MemoryPool::free(void* object)
{
	auto result = mPool->mMap.find(object);
	// 메모리 풀 소속이 아닌 엉뚱한 애를 해제하려고 하면(ex, 배열을 받고 중간부터 해제하려고 하는 경우) 서버 크래시낸다.
	if (result == mPool->mMap.end())
	{
		// 중요한 녀석이니 에러 메시지를 찍고 크래시를 낸다.
		assert(false && "잘못된 메모리를 해제하려고 함");
		exit(0);
	}
	int nIndex = mPool->mMap[object];
	
	if (nIndex < nPoolSize)
	{
		// lock
		EnterCriticalSection(&mPool->cs[nIndex]);
		mPool->memory[nIndex].push((BIT_8 *)object);
		LeaveCriticalSection(&mPool->cs[nIndex]);
		// unlock
	}
	else
	{
		// 엄청 큰걸 해제해줌
		delete (object);
	}
}

void MemoryPool::makeBlock(int nIndex, int nLength)
{
	int nCount = ALLOCATED_SIZE / nLength;
	BIT_8* allocBlock = new BIT_8[ALLOCATED_SIZE];

	for (int j = 0; j < nCount; j++)
	{
		BIT_8* mBlock = allocBlock+(j*nLength);
		mMap[mBlock] = nIndex;
		memset(mBlock, 0, nLength);
		memory[nIndex].push(mBlock);
	}
}