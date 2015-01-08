#pragma once
#include "std.h"

#include "fun.h"

// 소켓 초기화
void Init_socket(SOCKET* sock,int sockType, bool isBind, PSOCKADDR_IN localaddr, int port);


void set_sockaddrin(PSOCKADDR_IN sockaddr,int port,BOOL isServer, u_long saddr,char *serverIp);

// 소켓 함수 오류 출력
void err_display(char *msg);
// 소켓 함수 오류 출력 후 종료
void err_quit(char *msg);

// TCP 소켓 송신 함수.. 
void tcp_send(SOCKET descSock,char* sendbuff, int size);


// TCP 소켓 수신 함수..
int tcp_recv(SOCKET s, char *buf, int len, int flags);
