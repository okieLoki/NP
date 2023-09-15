#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>

int main(){

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);

    bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    char sendline[255];
    char recvline[255];

    while(1){
        bzero(sendline, 255);
        bzero(recvline, 255);

        fgets(sendline, 255, stdin);

        sendto(sockfd, sendline, sizeof(sendline), 0, (struct sockaddr*) &servaddr, sizeof(servaddr));

        recvfrom(sockfd, recvline, sizeof(recvline), 0, (struct sockaddr*) &servaddr, sizeof(servaddr));

        printf("from server: %s", recvline);
    }
}