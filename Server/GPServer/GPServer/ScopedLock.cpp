#include "ScopedLock.h"

ScopedReadLock::ScopedReadLock(SRWLOCK *l) {
	lock = l;
	AcquireSRWLockShared(lock);
}

ScopedReadLock::~ScopedReadLock() {
	ReleaseSRWLockShared(lock);
}

ScopedWriteLock::ScopedWriteLock(SRWLOCK *l) {
	lock = l;
	AcquireSRWLockExclusive(lock);
}

ScopedWriteLock::~ScopedWriteLock() {
	ReleaseSRWLockExclusive(lock);
}
