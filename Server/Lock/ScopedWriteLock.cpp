#include "ScopedWriteLock.h"

ScopedWriteLock::ScopedWriteLock(SRWLOCK *l) {
	lock = l;
	AcquireSRWLockExclusive(lock);
}

ScopedWriteLock::~ScopedWriteLock() {
	ReleaseSRWLockExclusive(lock);
}
