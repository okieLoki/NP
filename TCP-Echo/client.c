#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    char sendline[255];
    char recvline[255];

    while (1)
    {
        bzero(sendline, 255);
        bzero(recvline, 255);

        fgets(sendline, 255, stdin);

        write(sockfd, sendline, strlen(sendline));

        read(sockfd, sendline, 255);

        printf("echoing back from server: %s", sendline);
    }

    close(sockfd);
}