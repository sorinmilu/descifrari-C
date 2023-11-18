// client.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    // Create socket
    int client_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sockfd == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server's IP address
    server_address.sin_port = htons(8080);

    // Connect to the server
    if (connect(client_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to server");
        close(client_sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server.\n");

    // Send message to the server
    const char *message = "Hello from the client!";
    ssize_t sent_bytes = send(client_sockfd, message, strlen(message), 0);
    if (sent_bytes == -1) {
        perror("Error sending message");
        close(client_sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Message sent to the server: %s\n", message);

    // Receive response from the server
    char buffer[BUFFER_SIZE];
    ssize_t received_bytes = recv(client_sockfd, buffer, sizeof(buffer), 0);
    if (received_bytes <= 0) {
        perror("Error receiving response");
        close(client_sockfd);
        exit(EXIT_FAILURE);
    }

    buffer[received_bytes] = '\0';
    printf("Received response from server: %s\n", buffer);

    // Close socket
    close(client_sockfd);

    return 0;
}
