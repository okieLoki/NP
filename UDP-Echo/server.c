#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>


int main(){

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr;

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);

    bind(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    char buffer[255];

    int len = sizeof(servaddr);

    while(1){
        bzero(buffer, 255);

        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*) &servaddr, (struct socklen_t*) &len);

        printf("From client %s", buffer);

        char *token = strtok(buffer, " ");

        int sum = 0;

        while(token != NULL){
            sum += atoi(token);
            token = strtok(NULL, " ");
        }

        char sum_str[10];
        snprintf(sum_str, 10, "%d", sum);

        sendto(sockfd, sum_str, sizeof(sum_str), 0, (struct sockaddr*) &servaddr, len);
    }
}