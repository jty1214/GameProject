#pragma once

#include <Windows.h>

void SpinReadLock(SRWLOCK *lock, int num);
void SpinWriteLock(SRWLOCK *lock, int num);