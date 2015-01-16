#include "Markup.h"
#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <process.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

#define BUFSIZE 1024

typedef struct
{
	SOCKET hCIntSock;
	SOCKADDR_IN cIntAddr;
} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

typedef struct
{
	OVERLAPPED overlapped;
	char buffer[BUFSIZE];
	WSABUF wsaBuf;
} PER_IO_DATA, *LPPER_IO_DATA;

DWORD WINAPI CompletionThread(LPVOID pComPort);

void ErrorHandling(char *message);
string GetXMLData(CMarkup xml, char *elem, char *attrib);

int main()
{
	CMarkup xml;
	string port;

	xml.Load("Server.xml");
	
	port = GetXMLData(xml, "PORT", "number");
		

	WSADATA wsaData;
	HANDLE hCompletionPort;

	SYSTEM_INFO SystemInfo;

	SOCKADDR_IN servAddr;

	LPPER_IO_DATA PerIoData;

	LPPER_HANDLE_DATA PerHandleData;

	SOCKET hServSock;
	int RecvBytes;
	int i, Flags;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStratup() error!");

	hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	GetSystemInfo(&SystemInfo);

	for (i = 0; i < SystemInfo.dwNumberOfProcessors; i++)
	{
		CreateThread(NULL, NULL, CompletionThread, (LPVOID)hCompletionPort, 0, NULL);
	}

	hServSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(stoi(port));

	bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr));
	listen(hServSock, 5);

	while (true)
	{
		SOCKET hCIntSock;
		SOCKADDR_IN cIntAddr;
		int addrLen = sizeof(cIntAddr);

		hCIntSock = accept(hServSock, (SOCKADDR*)&cIntAddr, &addrLen);
		PerHandleData = (LPPER_HANDLE_DATA)malloc(sizeof(PER_HANDLE_DATA));
		PerHandleData->hCIntSock = hCIntSock;
		memcpy(&(PerHandleData->cIntAddr), &cIntAddr, addrLen);

		CreateIoCompletionPort((HANDLE)hCIntSock, hCompletionPort, (DWORD)PerHandleData, 0);

		PerIoData = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
		memset(&(PerIoData->overlapped), 0, sizeof(OVERLAPPED));
		PerIoData->wsaBuf.len = BUFSIZE;
		PerIoData->wsaBuf.buf = PerIoData->buffer;

		Flags = 0;

		WSARecv(PerHandleData->hCIntSock,
			&(PerIoData->wsaBuf),
			1,
			(LPDWORD)&RecvBytes,
			(LPDWORD)&Flags,
			&(PerIoData->overlapped),
			NULL
			);
	}

	return 0;
}

DWORD WINAPI CompletionThread(LPVOID pComPort)
{
	HANDLE hCompletionPort = (HANDLE)pComPort;

	DWORD BytesTransferred;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_DATA PerIoData;
	DWORD flags;

	while (true)
	{
		GetQueuedCompletionStatus(hCompletionPort,
			&BytesTransferred,
			(LPDWORD)&PerHandleData,
			(LPOVERLAPPED*)&PerIoData,
			INFINITE
			);

		if (BytesTransferred == 0)
		{
			closesocket(PerHandleData->hCIntSock);
			free(PerHandleData);
			free(PerIoData);
			continue;
		}
		PerIoData->wsaBuf.buf[BytesTransferred-1] = '\0';
#if PRINT_LOG
		printf("%s\n", PerIoData->wsaBuf.buf);
#endif
		PerIoData->wsaBuf.len = BytesTransferred;
		WSASend(PerHandleData->hCIntSock, &(PerIoData->wsaBuf), 1, NULL, 0, NULL, NULL);

		memset(&(PerIoData->overlapped), 0, sizeof(OVERLAPPED));
		PerIoData->wsaBuf.len = BUFSIZE;
		PerIoData->wsaBuf.buf = PerIoData->buffer;

		flags = 0;
		WSARecv(PerHandleData->hCIntSock, &(PerIoData->wsaBuf), 1, NULL, &flags, &(PerIoData->overlapped), NULL);
	}
	return 0;
}

void ErrorHandling(char *message)
{
#if PRINT_LOG
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
#endif
}

string GetXMLData(CMarkup xml, char *elem, char *attrib)
{
	xml.FindElem("SERVER");
	xml.IntoElem();
	xml.FindElem(elem);
	return xml.GetAttrib(attrib);
}