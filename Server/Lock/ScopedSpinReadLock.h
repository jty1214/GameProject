#pragma once

#include <Windows.h>
#include "SpinLock.h"

class ScopedSpinReadLock {
	SRWLOCK *lock;
	ScopedSpinReadLock(SRWLOCK *lock, int num);
	~ScopedSpinReadLock();
};