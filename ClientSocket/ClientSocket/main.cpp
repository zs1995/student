#include "udp.h"

int main(int argc,char **argv)
{

	WSADATA wsaData;
	SOCKET sockfd;

	int n,count1 = 0;
	char *recvline = NULL;

	struct sockaddr_in servaddr;
	struct hostent *host;

	recvline =(char *)malloc(100);

	if ( WSAStartup(MAKEWORD(2,2), &wsaData) != 0 )
	{
		printf("Init Windows Socket Failed::%d",GetLastError());
		return -1;
	}


	if((host = gethostbyname("192.168.10.102")) == NULL)
	{
		printf("gethostbyname error");
	}
	
	memset(&servaddr,0,sizeof(sockaddr_in));

	if((sockfd = socket(AF_INET,SOCK_STREAM,0))< 0)
	{
		printf("socket error");
	}


	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(18000);
	//servaddr.sin_addr.S_un.S_addr = INADDR_ANY;
	//servaddr.sin_addr.s_addr = inet_addr("192.168.10.102");
	servaddr.sin_addr = *((struct in_addr*)host->h_addr);

	memset(servaddr.sin_zero, 0x00, 8);

	if(connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
	{
		printf("connect error %d",GetLastError());
	}

	n = send(sockfd,"hello",strlen("hello"),0);
	if ( n == SOCKET_ERROR )
	{
		printf("Send Info Error::%d",GetLastError());
	}


	char recvtmp[10] = {0};
	while(true)
	{
		if((n = recv(sockfd,recvline+count1,2,0)) > 0)
		{
			count1 += n;
			memcpy(recvtmp,recvline,count1);
			printf("%s\n",recvtmp);
		}
	}

	getchar();

	free(recvline);
	recvline = NULL;
	shutdown(sockfd,2);
	closesocket(sockfd);
	WSACleanup();

	return 0;
}
