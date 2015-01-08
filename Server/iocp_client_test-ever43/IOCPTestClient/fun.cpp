#include "fun.h"

// 소켓 초기화
void Init_socket(SOCKET* sock,int sockType, bool isBind, PSOCKADDR_IN localaddr, int port)
{
	int retval;
	// 윈속 초기화
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)	
	{
		::ExitProcess(-1);
	}
	
	// socket(
	(*sock) = socket(AF_INET, sockType, 0);
	if(*sock == INVALID_SOCKET) err_quit("socket()");
	
	
	if( isBind )
	{
		// bind()
		//SOCKADDR_IN			localaddr;
		ZeroMemory(&(*localaddr), sizeof(*localaddr));
		(localaddr)->sin_family		= AF_INET;
		(localaddr)->sin_port			= htons(port);
		(localaddr)->sin_addr.s_addr   = htonl(INADDR_ANY);
		retval		= bind(*sock, (SOCKADDR*)&(*localaddr), 
			sizeof(*localaddr));
	}
}


void set_sockaddrin(PSOCKADDR_IN sockaddr,int port,BOOL isServer, u_long saddr,char *serverIp)
{
	ZeroMemory(&(*sockaddr), sizeof(*sockaddr));
	(*sockaddr).sin_family = AF_INET;
	(*sockaddr).sin_port = htons(port);
	//-------------------------------------------------------
	if( isServer )
		(*sockaddr).sin_addr.s_addr = htonl(saddr);
	else
		(*sockaddr).sin_addr.s_addr = inet_addr(serverIp);
	//-------------------------------------------------------
}


// 소켓 함수 오류 출력
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER|
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

// 소켓 함수 오류 출력 후 종료
void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER|
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	::ExitProcess(-1);
}

// TCP 소켓 송신 함수.. 
void tcp_send(SOCKET descSock,char* sendbuff, int size)
{
	int		nBytes		= size,
			nLeft,
			idx;

	int ret;


	//sendbuff에 size만큼 데이터를 채운다.

	nLeft	= nBytes;
	idx		= 0;

	while( nLeft > 0 )
	{
		ret	= send(descSock, &sendbuff[idx], nLeft, 0 );
		if( ret	== SOCKET_ERROR)
		{
			// error Handling
		}
		nLeft	-= ret;
		idx		+= ret;
	}

}


// TCP 소켓 수신 함수..
int tcp_recv(SOCKET s, char *buf, int len, int flags)
{
	int received;		char *ptr = buf;			int left = len;
	while(left > 0){
		received = recv(s, ptr, left, flags);
		if(received == SOCKET_ERROR) 		return SOCKET_ERROR;
		else if(received == 0) 				return -1;
		left -= received;
		ptr += received;
	}
	return (len - left);
}