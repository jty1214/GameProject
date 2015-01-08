#include "std.h"
#pragma comment(lib,"ws2_32.lib")

#define TOTALCOUNT 3000
#define BUFSIZE 128
int Count=0;


int main()
{
	int i;
	char buf[BUFSIZE];

	// 소켓 초기화
	SOCKET mySocket[TOTALCOUNT];

	for(i =0 ; i<TOTALCOUNT; i++)
	{
		Init_socket(&mySocket[i],SOCK_STREAM,FALSE,NULL,NULL);
	}

	// 접속할 서버 세팅
	SOCKADDR_IN serverAddr;
	set_sockaddrin(&serverAddr,9000,FALSE,NULL,"127.0.0.1");

	// 접속
	for(i=0; i<TOTALCOUNT; i++){
		if( connect(mySocket[i],(SOCKADDR*)&serverAddr,sizeof(serverAddr)) == SOCKET_ERROR )
			err_quit("접속실패");
		printf("연결됨 %d개 \r",++Count);
		Sleep(1);
	}



	while(1){
	// 메세지 전송 :
	for(i=0; i<TOTALCOUNT; i++)
	{
		sprintf(buf,"안녕 : %d",i);
		tcp_send(mySocket[i],buf,BUFSIZE);
		printf("SEND : %d \r",i);
		Sleep(5);
	}

	printf("\n 메세지를 다 보냈습니다. 보낸 메세지를 받습니다. ");

	printf("\n");
	

	// 메세지 받는다
	for(i=0; i<TOTALCOUNT; i++)
	{
		tcp_recv(mySocket[i],buf,BUFSIZE,0);
		printf("받은 메세지 RECV : %s \r",buf);
		Sleep(3);
	}
	
	}


	printf("\n");
	system("pause");

	// 닫기 
	printf("\n엔터를 누르시면 소켓을 닫습니다.");
	
	for(i=0; i<TOTALCOUNT; i++)
	{
		closesocket(mySocket[i]);
		printf("닫음 %d개 \r",--Count);
	}





return 0;
}



