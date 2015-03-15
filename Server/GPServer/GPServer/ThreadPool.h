#pragma once

#include <iostream>
#include <functional> 
#include <windows.h>

#define WORK_MAX  7
#define THREAD_MAX      20

using namespace std;
using namespace std::placeholders;

typedef function<DWORD()> WORK;

typedef struct __WorkerThread
{
	HANDLE hThread;
	DWORD idThread;
} WorkerThread;

typedef struct
{
	WORK workList[WORK_MAX];
	//LPVOID pParam[WORK_MAX];
	DWORD wResult[WORK_MAX];
	HANDLE circularEvent;

	WorkerThread workerThreadList[THREAD_MAX];
	HANDLE workerEventList[THREAD_MAX];

	DWORD idxOfCurrentWork;
	DWORD idxOfLastAddedWork;
	DWORD cntOfCurrentWork;
	DWORD cntOfLastAddedWork;
	// Number of Thread;
	DWORD threadIdx; // Pool에 존재하는 Thread 의 개수
}_ThreadPool;

typedef struct {
	_ThreadPool *gThreadPool;
	LPVOID pParam;
}ThreadParam;

DWORD AddWorkToPool(_ThreadPool *gThreadPool, WORK work);
int GetWorkFromPool(_ThreadPool *gThreadPool);
DWORD MakeThreadToPool(_ThreadPool *gThreadPool, DWORD numOfThread);
void WorkerThreadFunction(LPVOID pParam);
void initThreadPool(_ThreadPool *gThreadPool);

//************************************************************//
// Mutex 관련 함수들
// gThreadPool에 대한 접근을 보호하기 위해 정의
//************************************************************//
/*
static HANDLE mutex = NULL;

void InitMutex(void)
{
mutex = CreateMutex(NULL, FALSE, NULL);
}

void DeInitMutex(void)
{
BOOL ret = CloseHandle(mutex);
}

void AcquireMutex(void)
{
DWORD ret = WaitForSingleObject(mutex, INFINITE);

if (ret == WAIT_FAILED)
{
printf("Error Occur! \n");
}
}

void ReleaseMutex(void)
{
BOOL ret = ReleaseMutex(mutex);

if (ret == 0)
{
printf("Error Occur! \n");
}
}
*/