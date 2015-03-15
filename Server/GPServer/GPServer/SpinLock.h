#pragma once

#include <Windows.h>

class SpinLock {
	SRWLOCK *lock;
	SpinLock(SRWLOCK *l);
	void SpinReadLock();
	void SpinReadUnLock();
	void SpinWriteLock();
	void SpinWriteUnLock();
};