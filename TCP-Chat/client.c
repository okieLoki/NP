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

    struct sockaddr_in cliaddr;

    bzero(&cliaddr, sizeof(cliaddr));

    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(22000);
    cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

    char sendline[255];
    char recvline[255];

    while (1)
    {
        bzero(sendline, 255);
        printf("Client: ");
        fgets(sendline, 255, stdin);

        if (strcmp(sendline, "exit\n") == 0)
        {
            break;
        }
        write(sockfd, sendline, strlen(sendline));

        bzero(recvline, 255);
        read(sockfd, recvline, 255);

        printf("Server: %s", recvline);
    }

    close(sockfd);
}