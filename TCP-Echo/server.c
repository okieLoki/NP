#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

char* reverseStr(char* buffer){
	int len = strlen(buffer);
	char* rev = (char*)malloc(len*sizeof(char));
	for(int i = 0; i < len; i++){
		rev[i] = buffer[len-i-1];
	}
	return rev;
}

int main()
{
	int sockfd, newsockfd;	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(22000);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	listen(sockfd, 10);

	char buffer[255];

	newsockfd = accept(sockfd, (struct sockaddr *)NULL, NULL);

	while (1)
	{
		bzero(buffer, 255);

		read(newsockfd, buffer, 255);

		printf("from client: %s", buffer);

		char* rev = reverseStr(buffer);

		write(newsockfd, rev, strlen(rev));
	}

	close(newsockfd);
}
