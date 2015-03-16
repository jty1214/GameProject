#pragma once

#include <Windows.h>

class ScopedReadLock {
	SRWLOCK *lock;
	ScopedReadLock(SRWLOCK *lock);
	~ScopedReadLock();
};