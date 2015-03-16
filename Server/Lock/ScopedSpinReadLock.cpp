#include "ScopedSpinReadLock.h"

ScopedSpinReadLock::ScopedSpinReadLock(SRWLOCK *l, int num) {
	lock = l;
	SpinReadLock(lock, num);
}

ScopedSpinReadLock::~ScopedSpinReadLock() {
	ReleaseSRWLockShared(lock);
}