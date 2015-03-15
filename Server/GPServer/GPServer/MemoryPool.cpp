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

		// ���� ��� ������ �޸� ����� ���°��, �߰�����ŭ �Ҵ��� ���ش�.
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
		// ��û ū�Ŷ��, OS���� �Ҵ��ϴ� ���� �̵�
		// �̷��Ա��� ū ��ü��, �����ڿ� �Ҹ��ڸ� ���� �ҷ����� �ʴ´�. (�Ҹ��ڿ��� ó�� ����� �������� ���� TT)
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

		// ���� ��� ������ �޸� ����� ���°��, �߰�����ŭ �Ҵ��� ���ش�.
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
		// ��û ū�Ŷ��, OS���� �Ҵ��ϴ� ���� �̵�
		BIT_8* alloc = new BIT_8[size];
		mPool->mMap[alloc] = nPoolSize;
		return alloc;
	}
}

void MemoryPool::free(void* object)
{
	auto result = mPool->mMap.find(object);
	// �޸� Ǯ �Ҽ��� �ƴ� ������ �ָ� �����Ϸ��� �ϸ�(ex, �迭�� �ް� �߰����� �����Ϸ��� �ϴ� ���) ���� ũ���ó���.
	if (result == mPool->mMap.end())
	{
		// �߿��� �༮�̴� ���� �޽����� ��� ũ���ø� ����.
		assert(false && "�߸��� �޸𸮸� �����Ϸ��� ��");
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
		// ��û ū�� ��������
		delete (object);
	}
}

void MemoryPool::makeBlock(int nIndex, int nLength)
{
	int nCount = ALLOCATED_SIZE / nLength;
	BIT_8* allocBlock = new BIT_8[ALLOCATED_SIZE];

	for (int j = 0; j < nCount; j++)
	{
		BIT_8* mBlock = allocBlock + (j*nLength);
		mMap[mBlock] = nIndex;
		memset(mBlock, 0, nLength);
		memory[nIndex].push(mBlock);
	}
}