#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int sock_fd, comm_fd;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    bzero(&server, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = htons(22000);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock_fd, (struct sockaddr *)&server, sizeof(server));

    listen(sock_fd, 5);

    char buffer[100];

    comm_fd = accept(sock_fd, (struct sockaddr *)NULL, NULL);

    while (1)
    {
        bzero(buffer, 100);

        read(comm_fd, buffer, 100);

        printf("Client: %s", buffer);

        for (int i = 0; i < strlen(buffer); i++)
        {
            write(comm_fd, &buffer[i], 1);
            write(comm_fd, " ", 1);
        }
    }

    close(comm_fd);
}
