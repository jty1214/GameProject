#pragma once

#include <WinSock2.h>

#define BUFSIZE 1024

int SocketCount = 0;

const int SERVER_PORT = 9000;

typedef struct //소켓정보를구조체화.
{
	SOCKET hClntSock;
	SOCKADDR_IN clntAddr;
} PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

typedef struct // 소켓의버퍼정보를구조체화.
{
	OVERLAPPED overlapped;
	char buffer[BUFSIZE];
	WSABUF wsaBuf;
} PER_IO_DATA, *LPPER_IO_DATA;
/*
소켓 버퍼 정보를 구조체로 만드는데 이때 WSABUF 와 overlapped 를 포함한다.
WSABUF 는WSASend 나WSARecv 함수의 인자로 전달되는 버퍼에 사용되는 구조체 이기에 포함 되고
overlapped 구조체 변수를 넣어주는건 현재 완료된 입출력 정보를 얻어 낼때 사용 된다.
*/