#pragma once
/*
#include "MemoryPool.h"

// ���� ������ ����

template <typename T>
class Ptr
{
	T* object;

public:
	Ptr()
	{
		object = MemoryPool::getInstance()->malloc<T>();
	}
	~Ptr()
	{
		MemoryPool::getInstance()->free<T>(object);
	}

	T* operator ->()
	{
		return object;
	}

	void operator =(const T&& pObject)
	{
		*object = pObject;
	}

	T& operator * ()
	{
		return *object;
	}
};
*/