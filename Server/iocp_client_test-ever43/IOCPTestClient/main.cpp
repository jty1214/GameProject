#include "std.h"
#pragma comment(lib,"ws2_32.lib")

#define TOTALCOUNT 3000
#define BUFSIZE 128
int Count=0;


int main()
{
	int i;
	char buf[BUFSIZE];

	// ���� �ʱ�ȭ
	SOCKET mySocket[TOTALCOUNT];

	for(i =0 ; i<TOTALCOUNT; i++)
	{
		Init_socket(&mySocket[i],SOCK_STREAM,FALSE,NULL,NULL);
	}

	// ������ ���� ����
	SOCKADDR_IN serverAddr;
	set_sockaddrin(&serverAddr,9000,FALSE,NULL,"127.0.0.1");

	// ����
	for(i=0; i<TOTALCOUNT; i++){
		if( connect(mySocket[i],(SOCKADDR*)&serverAddr,sizeof(serverAddr)) == SOCKET_ERROR )
			err_quit("���ӽ���");
		printf("����� %d�� \r",++Count);
		Sleep(1);
	}



	while(1){
	// �޼��� ���� :
	for(i=0; i<TOTALCOUNT; i++)
	{
		sprintf(buf,"�ȳ� : %d",i);
		tcp_send(mySocket[i],buf,BUFSIZE);
		printf("SEND : %d \r",i);
		Sleep(5);
	}

	printf("\n �޼����� �� ���½��ϴ�. ���� �޼����� �޽��ϴ�. ");

	printf("\n");
	

	// �޼��� �޴´�
	for(i=0; i<TOTALCOUNT; i++)
	{
		tcp_recv(mySocket[i],buf,BUFSIZE,0);
		printf("���� �޼��� RECV : %s \r",buf);
		Sleep(3);
	}
	
	}


	printf("\n");
	system("pause");

	// �ݱ� 
	printf("\n���͸� �����ø� ������ �ݽ��ϴ�.");
	
	for(i=0; i<TOTALCOUNT; i++)
	{
		closesocket(mySocket[i]);
		printf("���� %d�� \r",--Count);
	}





return 0;
}



