#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX 100
#define PORT 3500

void sigint_handler(int signum)
{
    printf("SIGINT signal receieved and server stopped\n");
    exit(EXIT_SUCCESS);
}

void handle_client(int client_sockfd)
{
    while (1)
    {
        char received_command[MAX];
        memset(received_command, 0, MAX);
        read(client_sockfd, received_command, MAX);
        printf("Received command from client: %s\n", received_command);

        if (strncmp(received_command, "stop", 4) == 0)
        {
            printf("Stopping communication with client\n");
            break;
        }

        int command_return = system(received_command);
        printf("command_return = %d\n", command_return);

        int x = htonl(command_return);
        send(client_sockfd, &x, sizeof(x), 0);
    }

    close(client_sockfd);
    exit(EXIT_SUCCESS);
}

int main()
{
    signal(SIGINT, sigint_handler);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int option_value = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(option_value));

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
    {
        perror("Couldn't bind the socket");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 5) < 0)
    {
        perror("Couldn't listen for connections");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        struct sockaddr_in client_addr;
        int length_of_address = sizeof(client_addr);
        int client_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &length_of_address);
        if (client_sockfd < 0)
        {
            perror("Couldn't establish connection with client");
            continue;
        }

        pid_t pid = fork();
        if (pid == 0)  // Child process
        {
            close(sockfd);  // Child doesn't need the listening socket
            handle_client(client_sockfd);
        }
        else if (pid > 0)  // Parent process
        {
            close(client_sockfd);  // Parent doesn't need the client socket
        }
        else
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        // Handle zombie processes
        while (waitpid(-1, NULL, WNOHANG) > 0);
    }

    close(sockfd);
    return 0;
}

