#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1" // Localhost for testing
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    char input[BUFFER_SIZE];
    int bytesReceived;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Receive and print the welcome message
    bytesReceived = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        printf("Server: %s", buffer);
    } else {
        perror("Failed to receive welcome message");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Main client loop
    while (1) {
        printf("Enter command ('REVERSE <string>' or 'UPPER <string>') or 'exit' to quit: ");
        fgets(input, sizeof(input), stdin);

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Send the command to the server
        if (send(sockfd, input, strlen(input), 0) < 0) {
            perror("Send failed");
            break;
        }

        // Receive and print the response from the server
        bytesReceived = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            printf("Server: %s\n", buffer);
        } else {
            perror("Receive failed");
            break;
        }
    }

    // Close the socket
    close(sockfd);
    return 0;
}

