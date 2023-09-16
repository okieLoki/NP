#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;

    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(22000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock_fd, (struct sockaddr *)&server, sizeof(server));

    char input[100];
    char recvchar;

    while (1)
    {
        bzero(input, 100);

        printf("Enter a string: ");
        fgets(input, 100, stdin);

        write(sock_fd, input, strlen(input));

        printf("Server: ");

        while(read(sock_fd, &recvchar, 1)> 0){
            printf("%c ", recvchar);
        }
    }

    close(sock_fd);
}
