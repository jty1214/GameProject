#pragma once
#include "std.h"

#include "fun.h"

// ���� �ʱ�ȭ
void Init_socket(SOCKET* sock,int sockType, bool isBind, PSOCKADDR_IN localaddr, int port);


void set_sockaddrin(PSOCKADDR_IN sockaddr,int port,BOOL isServer, u_long saddr,char *serverIp);

// ���� �Լ� ���� ���
void err_display(char *msg);
// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg);

// TCP ���� �۽� �Լ�.. 
void tcp_send(SOCKET descSock,char* sendbuff, int size);


// TCP ���� ���� �Լ�..
int tcp_recv(SOCKET s, char *buf, int len, int flags);
