#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){

    int clientfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in cliaddr;

    bzero(&cliaddr, sizeof(cliaddr));

    cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    cliaddr.sin_port = htons(22000);
    cliaddr.sin_family = AF_INET;

    bind(clientfd, (struct sockaddr*) &clientfd, sizeof(clientfd));

    char sendline[255];
    char recvline[255];

    int len = sizeof(cliaddr);

    while(1){
        bzero(sendline, 255);
        printf("Client:  ");
        fgets(sendline, 255, stdin);

        if(strcmp(sendline, "exit\n") == 0){
            break;
        }
        
        sendto(clientfd, sendline, 255, 0, (struct sockaddr*) &cliaddr, len);

        bzero(recvline, 255);

        recvfrom(clientfd, recvline, 255, 0, (struct sockaddr*) &cliaddr, (struct socklen_t*) &len);

        printf("Server: %s \n", recvline);
    }

    close(clientfd);
}