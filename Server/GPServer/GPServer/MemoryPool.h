#pragma once

#include <map>
#include <stack>
#include <Windows.h>

#define BIT_8 char

const int ALLOCATED_SIZE = (1 << 20);	// �� �޸� Ǯ�� �� �Ҵ緮
const int nLength[] = {	// �� �޸� ����� ũ���
	(1 << 5),
	(1 << 8),
	(1 << 11),
	(1 << 16),
	(1 << 18),
	(1 << 20)
};
const int nPoolSize = sizeof(nLength) / sizeof(nLength[0]);	// �޸� Ǯ�� �� ����

class MemoryPool
{
private:
	std::stack<BIT_8* > memory[nPoolSize];
	std::map<void *, int> mMap;
	CRITICAL_SECTION cs[nPoolSize];
public:
	template <typename T>
	static T* malloc(const int size = 1);
	static void* malloc(std::size_t size);

	static void free(void* object);

private:
	MemoryPool();
	void makeBlock(int nLength, int nCount);
public:
	static void makeMemoryPool() { mPool = new MemoryPool(); }
	static MemoryPool* getInstance() { return mPool; }
	static int getIndex(int nSize);
private:
	static MemoryPool* mPool;
};

template <typename T>
struct destructor {
	void operator()(T* c){ MemoryPool::getInstance()->free(c); }
};