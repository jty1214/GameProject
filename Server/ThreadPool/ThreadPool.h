#pragma once

#include <iostream>
#include <functional> 
#include <windows.h>

#define WORK_MAX  7
#define THREAD_MAX      50

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
//************************************************************//
// Thread Pool 초기화를 위한 함수
//
//************************************************************//
void initThreadPool(_ThreadPool *gThreadPool) {
	gThreadPool->idxOfCurrentWork = 0;
	gThreadPool->idxOfLastAddedWork = 0;
	gThreadPool->cntOfCurrentWork = 0;
	gThreadPool->cntOfLastAddedWork = 0;
	gThreadPool->threadIdx = 0;
	gThreadPool->circularEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	memset(gThreadPool->wResult, 0, WORK_MAX);
	memset(gThreadPool->workerEventList, 0, THREAD_MAX);
	memset(gThreadPool->workerThreadList, 0, THREAD_MAX);
	
}
//************************************************************//
// Thread Pool에 Work 를 등록시키기 위한 함수
//
//************************************************************//
DWORD AddWorkToPool(_ThreadPool *gThreadPool, WORK work)
{
	//AcquireMutex();
	if (gThreadPool->idxOfLastAddedWork >= WORK_MAX)
	{		
		WaitForSingleObject(gThreadPool->circularEvent, INFINITE);
		gThreadPool->idxOfLastAddedWork = 0;
	}

	// Work 등ìi록¤I.
	gThreadPool->workList[gThreadPool->idxOfLastAddedWork++] = work;
	gThreadPool->cntOfLastAddedWork++;
	//gThreadPool->pParam[gThreadPool->idxOfLastAddedWork++] = pParam;

	// Work 등록 후 대기중인 쓰레드 들을 모두 꺠워 일을 시작하도록 함.
	// 모두를 깨울 필요 없으므로 정교함이 떨어지는 부분이다.
	for (DWORD i = 0; i<gThreadPool->threadIdx; i++)
		SetEvent(gThreadPool->workerEventList[i]);

	//ReleaseMutex();

	return 1;
}


//************************************************************//
// Thread에서 Work 을 가져올 때 호출되는 함수
// gThreadPool에 대한 접근을 보호하기 위해 정의
//************************************************************//
int GetWorkFromPool(_ThreadPool *gThreadPool)
{
	//AcquireMutex();	
	// 현재 처리해야 할 Work 가 존재하지 않다면..
	if (gThreadPool->idxOfCurrentWork >= WORK_MAX) {
		SetEvent(gThreadPool->circularEvent);
		gThreadPool->idxOfCurrentWork = 0;
	}
	if (gThreadPool->cntOfCurrentWork >= gThreadPool->cntOfLastAddedWork)
	{
		//ReleaseMutex();
		return -1;
	}		
	//work = gThreadPool->workList[gThreadPool->idxOfCurrentWork++];
	//ReleaseMutex();
	gThreadPool->cntOfCurrentWork++;
	return gThreadPool->idxOfCurrentWork++;
}


//************************************************************//
// Thread Pool 생성
// 전달되는 인자값에 따라 Thread 생성
//
//************************************************************//
DWORD MakeThreadToPool(_ThreadPool *gThreadPool, DWORD numOfThread)
{
	//InitMutex();

	DWORD capacity = WORK_MAX - (gThreadPool->threadIdx);

	if (capacity < numOfThread)
		numOfThread = capacity;

	for (DWORD i = 0; i < numOfThread; i++)
	{
		DWORD idThread;
		HANDLE hThread;
		ThreadParam *tp = new ThreadParam;
		tp->gThreadPool = gThreadPool;
		tp->pParam = (LPVOID)gThreadPool->threadIdx;

		gThreadPool->workerEventList[gThreadPool->threadIdx]
			= CreateEvent(NULL, FALSE, FALSE, NULL);

		hThread = CreateThread(
			NULL, 0,
			(LPTHREAD_START_ROUTINE)WorkerThreadFunction,
			(LPVOID)tp,
			0, &idThread
			);

		gThreadPool->workerThreadList[gThreadPool->threadIdx].hThread = hThread;
		gThreadPool->workerThreadList[gThreadPool->threadIdx].idThread = idThread;

		gThreadPool->threadIdx++;
	}
	return numOfThread; // Return added thread number!
}
DWORD* GetResult(_ThreadPool *gThreadPool) {
	return gThreadPool->wResult;
}

// 전달 되어야 할 대상
void WorkerThreadFunction(LPVOID pParam)
{
	ThreadParam tp = *(ThreadParam *)pParam;
	WORK workFunction;
	//LPVOID param;
	HANDLE event = tp.gThreadPool->workerEventList[(DWORD)tp.pParam];	
	WorkerThread wThread = tp.gThreadPool->workerThreadList[(DWORD)tp.pParam];	
	while (1)
	{
		// work = gThreadPool->workList[gThreadPool->idxOfCurrentWork++];
		int index = GetWorkFromPool(tp.gThreadPool);		
		//param = tp.gThreadPool->pParam[index];
		
		if (index == -1)
		{
			WaitForSingleObject(event, INFINITE);
			continue;
		}		
		workFunction = tp.gThreadPool->workList[index];
		try {
			tp.gThreadPool->wResult[index] = workFunction();
		}
		catch (const bad_function_call& e) {			
			cout << index << ": " << e.what() << '\n';
			//AddWorkToPool(tp.gThreadPool, tp.gThreadPool->workList[index]);
		}
	}
	delete (ThreadParam *)pParam;
}

template <typename T, typename ...Args>
function<DWORD()> asyncWorkInit(_ThreadPool *gThreadPool, T &object, DWORD (T::*mf)(Args...)) {
	function<DWORD()> fuc = bind((object.*mf), &object, 2);
	function<DWORD()> asyncWork = bind(AddWorkToPool, gThreadPool, fuc);
	return asyncWork;
}
