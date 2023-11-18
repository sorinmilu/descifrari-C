// server.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    // Create socket
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    // Bind socket to address
    if (bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_sockfd, 5) == -1) {
        perror("Error listening");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");

    // Accept incoming connections
    int client_sockfd = accept(server_sockfd, NULL, NULL);
    if (client_sockfd == -1) {
        perror("Error accepting connection");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connection accepted. Waiting for message...\n");

    // Receive message from the client
    char buffer[BUFFER_SIZE];
    ssize_t received_bytes = recv(client_sockfd, buffer, sizeof(buffer), 0);
    if (received_bytes <= 0) {
        perror("Error receiving message");
        close(client_sockfd);
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[received_bytes] = '\0';
    printf("Received message from client: %s\n", buffer);

    // Send response to the client
    const char *response = "Hello from the server!";
    ssize_t sent_bytes = send(client_sockfd, response, strlen(response), 0);
    if (sent_bytes == -1) {
        perror("Error sending response");
    } else {
        printf("Response sent to client: %s\n", response);
    }

    // Close sockets
    close(client_sockfd);
    close(server_sockfd);

    return 0;
}
