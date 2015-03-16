#include "SpinLock.h"

void SpinReadLock(SRWLOCK *lock, int num) {
	for (int i = 0; i < num;i++)
	if (TryAcquireSRWLockShared(lock))
		break;
}

void SpinWriteLock(SRWLOCK *lock, int num) {
	for (int i = 0; i < num; i++)
	if (TryAcquireSRWLockExclusive(lock))
		break;
}