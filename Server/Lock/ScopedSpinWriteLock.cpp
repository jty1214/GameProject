#include "ScopedSpinWriteLock.h"

ScopedSpinWriteLock::ScopedSpinWriteLock(SRWLOCK *l, int num) {
	lock = l;
	SpinWriteLock(lock, num);
}

ScopedSpinWriteLock::~ScopedSpinWriteLock() {
	ReleaseSRWLockShared(lock);
}