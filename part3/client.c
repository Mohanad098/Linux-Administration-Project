#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX 100

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        perror("Please pass the remote IP/Port as arguments");
        exit(EXIT_FAILURE);
    }

    // create an IPv4 and TCP socket
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_descriptor < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    char *ip_address = argv[1];
    int port_number = atoi(argv[2]);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    server_address.sin_addr.s_addr = inet_addr(ip_address);

    int status = connect(socket_descriptor, (struct sockaddr*)&server_address,
                         sizeof(server_address));
    if (status < 0)
    {
        perror("Couldn't connect with the server");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("Please enter command: ");
        char command[MAX];
        fgets(command, sizeof(command), stdin);

        // Send command to the server
        write(socket_descriptor, command, strlen(command));

        if (strncmp(command, "stop", 4) == 0)
        {
            printf("Stopping communication with server\n");
            break;
        }

        // Receive exit status from the server
        int command_return;
        read(socket_descriptor, &command_return, sizeof(int));
        printf("Exit status from server: %d\n", ntohl(command_return));
    }

    close(socket_descriptor);
    return 0;
}

