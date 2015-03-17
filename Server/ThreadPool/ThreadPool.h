#pragma once

#include <iostream>
#include <functional> 
#include <windows.h>
#include <vector>

#define WORK_MAX  10000
#define THREAD_MAX      20
#define THREAD_WAITING 0
#define THREAD_RUNNING 1

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
	DWORD wResult[WORK_MAX];
	HANDLE circularEvent;

	WorkerThread workerThreadList[THREAD_MAX];
	HANDLE workerEventList[THREAD_MAX];	
	INT32 statusEventList[THREAD_MAX];

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

static CRITICAL_SECTION m_cs;

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
	memset(gThreadPool->workerEventList, 0, THREAD_MAX * sizeof(HANDLE));
	memset(gThreadPool->statusEventList, THREAD_WAITING, THREAD_MAX * sizeof(INT32));
	//for (int i = 0; i < THREAD_MAX; i++)
	//	gThreadPool->statusEventList[i] = THREAD_RUNNING;
	memset(gThreadPool->workerThreadList, 0, THREAD_MAX * sizeof(WorkerThread));
	
}
//************************************************************//
// Thread Pool에 Work 를 등록시키기 위한 함수
//
//************************************************************//
DWORD AddWorkToPool(_ThreadPool *gThreadPool, WORK work)
{	
	if (gThreadPool->idxOfLastAddedWork >= WORK_MAX)
	{		
		WaitForSingleObject(gThreadPool->circularEvent, INFINITE);
		gThreadPool->idxOfLastAddedWork = 0;
	}	
	// Work 등ìi록¤I.
	gThreadPool->workList[gThreadPool->idxOfLastAddedWork] = work;	
	// Work 등록 후 대기중인 쓰레드 들을 모두 꺠워 일을 시작하도록 함.
	// 모두를 깨울 필요 없으므로 정교함이 떨어지는 부분이다.		
	if (gThreadPool->cntOfCurrentWork >= gThreadPool->cntOfLastAddedWork) {
		for (DWORD i = 0; i < gThreadPool->threadIdx; i++) {
			SetEvent(gThreadPool->workerEventList[i]);
		}
	}
	gThreadPool->idxOfLastAddedWork++;
	gThreadPool->cntOfLastAddedWork++;
	return 1;
}


//************************************************************//
// Thread에서 Work 을 가져올 때 호출되는 함수
// gThreadPool에 대한 접근을 보호하기 위해 정의
//************************************************************//
int GetWorkFromPool(_ThreadPool *gThreadPool)
{
	// 현재 처리해야 할 Work 가 존재하지 않다면..
	if (gThreadPool->idxOfCurrentWork >= WORK_MAX) {
		SetEvent(gThreadPool->circularEvent);
		gThreadPool->idxOfCurrentWork = 0;
	}
	if (gThreadPool->cntOfCurrentWork >= gThreadPool->cntOfLastAddedWork)
	{
		return -1;
	}
	//work = gThreadPool->workList[gThreadPool->idxOfCurrentWork++];
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
	InitializeCriticalSection(&m_cs);

	DWORD capacity = WORK_MAX - (gThreadPool->threadIdx);

	if (capacity < numOfThread)
		numOfThread = capacity;

	for (DWORD i = 0; i < numOfThread; i++)
	{
		DWORD idThread;
		HANDLE hThread;

		gThreadPool->workerEventList[gThreadPool->threadIdx]
			= CreateEvent(NULL, FALSE, FALSE, NULL);

		ThreadParam *tp = new ThreadParam;
		tp->gThreadPool = gThreadPool;
		tp->pParam = (LPVOID)gThreadPool->threadIdx;

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
	while (1)
	{		
		EnterCriticalSection(&m_cs);		
		int index = GetWorkFromPool(tp.gThreadPool);
		LeaveCriticalSection(&m_cs);	
		if (index == -1)
		{
			WaitForSingleObject(event, INFINITE);			
			continue;
		}	
			
		try {
			workFunction = tp.gThreadPool->workList[index];
			tp.gThreadPool->wResult[index] = workFunction();
		}
		catch (const bad_function_call& e) {
			cout << index << ": " << e.what() << '\n';
			//AddWorkToPool(tp.gThreadPool, tp.gThreadPool->workList[index]);
		}
	}
	delete (ThreadParam *)pParam;
}

template <class Functor, class Actor, class... Args>
DWORD DoAsync(_ThreadPool *gThreadPool, Functor&& func, Actor&& actor, Args&&... args) {
	std::function<DWORD()> async = bind(func, actor, args...);
	return AddWorkToPool(gThreadPool, async);
}

template <class Functor, class Actor, class... Args>
DWORD DoTimer(DWORD ms, _ThreadPool *gThreadPool, Functor&& func, Actor&& actor, Args&&... args) {

	std::function<DWORD()> async = bind(func, actor, args...);
	std::function<DWORD()> timer = bind(_TimeAfterWork, ms, async);
	return AddWorkToPool(gThreadPool, timer);
}

DWORD _TimeAfterWork(DWORD ms, WORK func)
{
	Sleep(ms);
	return func();
}