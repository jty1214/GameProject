#include <Windows.h>

class ScopedWriteLock {
	SRWLOCK *lock;
	ScopedWriteLock(SRWLOCK *l);
	~ScopedWriteLock();
};