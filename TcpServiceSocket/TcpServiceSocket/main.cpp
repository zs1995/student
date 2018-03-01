#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

int main(int argc,char **argv)
{
	WSADATA wsadata;
	SOCKET s;
	int ret;

	if(WSAStartup(MAKEWORD(2,2),&wsadata) != 0)
	{
	  printf("WSAStartup fail\n");
	}

	s = socket(AF_INET,SOCK_STREAM,0);

	if(s == INVALID_SOCKET)
	{
		printf("socket error\n");
	}

	struct sockaddr_in sockserveraddr,sockclientaddr;

	sockserveraddr.sin_family = AF_INET;
	sockserveraddr.sin_port = htons(18000);
	//sockserveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockserveraddr.sin_addr.S_un.S_addr = inet_addr("192.168.10.102");
	ret = bind(s,(sockaddr *)&sockserveraddr,sizeof(sockserveraddr));
	if( ret != SOCKET_ERROR)
	{
		printf("bind success\n");
	}

	ret = listen(s,10);
	if(ret != SOCKET_ERROR)
	{
		printf("listen success\n");
	}

	SOCKET serversocket;
	fd_set fdreadset;


	struct timeval timeout;
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;

	
	int length;
	char recvline[1024];
	memset(recvline,0,1024);

	u_long ul=1;
	ioctlsocket(s,FIONBIO,&ul); 

	int n = 0;
	int fd = 0;
	while(1)
	{

		//select()

		length = sizeof(sockclientaddr);
		serversocket = accept(s,(sockaddr *)&sockclientaddr,&length);

		FD_ZERO(&fdreadset);
		FD_SET(serversocket,&fdreadset);

		if(select(fd+1,&fdreadset,0,0,&timeout) != SOCKET_ERROR)
		{
			if(FD_ISSET(serversocket,&fdreadset))
			{
				n = recv(serversocket,recvline,2,0);
				printf("%s\n",recvline);
			}
		}

		
	
// 		if(serversocket == INVALID_SOCKET)
// 		{
// 
// 			printf("accept() faild! code:%d\n", WSAGetLastError());  
// 			closesocket(s); //¹Ø±ÕÌ×½Ó×Ö 
// 			//printf("accept success\n");
// 		}


		//send(serversocket,"my name",10,0);

	}

	shutdown(serversocket,2);
	closesocket(serversocket);

	shutdown(s,2);
	closesocket(s);
	WSACleanup();

	getchar();
	return 0;
}
