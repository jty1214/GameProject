#pragma once

#include <Windows.h>
#include "SpinLock.h"

class ScopedSpinWriteLock {
	SRWLOCK *lock;
	ScopedSpinWriteLock(SRWLOCK *lock, int num);
	~ScopedSpinWriteLock();
};