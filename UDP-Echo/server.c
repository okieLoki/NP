#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>


int main(){

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr, cliaddr;

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);

    bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    char buffer[255];

    int len = sizeof(cliaddr);

    while(1){
        bzero(buffer, 255);

        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*) &cliaddr, (struct socklen_t*) &len);

        printf("From client %s", buffer);

        sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*) &cliaddr, len);
    }
}