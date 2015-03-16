#include "ScopedReadLock.h"

ScopedReadLock::ScopedReadLock(SRWLOCK *l) {
	lock = l;
	AcquireSRWLockShared(lock);
}

ScopedReadLock::~ScopedReadLock() {
	ReleaseSRWLockShared(lock);
}