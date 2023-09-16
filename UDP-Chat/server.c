#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(){

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in servaddr, cliaddr;

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    char sendline[255];
    char recvline[255];

    int len = sizeof(cliaddr);

    while(1){
        bzero(recvline, 255);

        recvfrom(sockfd, recvline, 255, 0, (struct sockaddr*) &cliaddr, (socklen_t*)&len);
        printf("Client: %s\n", recvline);

        bzero(sendline, 255);

        printf("Server: ");
        fgets(sendline, 255, stdin);

        if(strcmp(sendline, "exit\n") == 0){
            break;
        }

        sendto(sockfd, sendline, 255, 0, (struct sockaddr*) &cliaddr, len);
    }

    close(sockfd);
}