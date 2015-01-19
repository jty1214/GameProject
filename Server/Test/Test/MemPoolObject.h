#pragma once

#include "MemoryPool.h"

class MemPoolObject
{
public :
	// Allocate
	void* operator new(std::size_t size) _THROW1(std::bad_alloc)
	{
		void * object = MemoryPool::malloc(size);

		return object;
	}

		void* operator new[](std::size_t size) _THROW1(std::bad_alloc)
	{
		void * object = MemoryPool::malloc(size);

		return object;
	}

	// Place Allocate

		void* operator new(std::size_t count, void* ptr) _THROW1(std::bad_alloc)
	{
		return ptr;
	}

		void* operator new[](std::size_t count, void* ptr) _THROW1(std::bad_alloc)
	{
		return ptr;
	}

	// Deallocate

	void operator delete(void * object) _THROW1(std::bad_alloc)
	{
		MemoryPool::free(object);
	}

	void operator delete[](void * object) _THROW1(std::bad_alloc)
	{
		MemoryPool::free(object);
	}

		void operator delete(void* ptr, std::size_t sz) _THROW1(std::bad_alloc)
	{
		MemoryPool::free(ptr);
	}
	
		void operator delete[](void* ptr, std::size_t sz) _THROW1(std::bad_alloc)
	{
		MemoryPool::free(ptr);
	}

	// Place Deallocate

	void operator delete  (void* ptr, void* place) _THROW1(std::bad_alloc)
	{
		puts("Place Deallocate �� �߻��� ���Դϴ�. � ��Ȳ���� Ȯ�� �� ������ ��ġ���ּ���.");
	}
	
	void operator delete[](void* ptr, void* place)  _THROW1(std::bad_alloc)
	{
		puts("Place Deallocate �� �߻��� ���Դϴ�. � ��Ȳ���� Ȯ�� �� ������ ��ġ���ּ���.");
	}

};