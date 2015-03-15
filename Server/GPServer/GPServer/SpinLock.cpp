#include "SpinLock.h"

SpinLock::SpinLock(SRWLOCK *l) {
	lock = l;
}

void SpinLock::SpinReadLock() {
	while (!TryAcquireSRWLockShared(lock));
}

void SpinLock::SpinReadUnLock() {
	ReleaseSRWLockShared(lock);
}

void SpinLock::SpinWriteLock() {
	while (!TryAcquireSRWLockExclusive(lock));
}

void SpinLock::SpinWriteUnLock() {
	ReleaseSRWLockExclusive(lock);
}