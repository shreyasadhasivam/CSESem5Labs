#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
	int len, result, sockfd, n=1;
	struct sockaddr_in address;
	char ch[256],buf[256];

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr= inet_addr("172.16.48.89");
	address.sin_port = htons(10204);
	len = sizeof(address);

	result = connect(sockfd,(struct sockaddr*)&address, len);
	if(result == -1)
	{
		perror("\nClient error");
		exit(1);
	}

	printf("\nEnter sentence: ");
	gets(ch);
	while(!(strcmp(ch,"Stop)")))
	{
		ch[strlen(ch)]='\0';
		write(sockfd,ch,strlen(ch));
		printf("STRING SENT BACK FROM SERVER IS....");
		while(n)
		{
			n = read(sockfd,buf,sizeof(buf));
			puts(buf);
			//exit(0);
		}
	}
	close(sockfd);
	return 0;
}