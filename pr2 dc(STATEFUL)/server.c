#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BACKLOG 5
#define BUFFER_SIZE 1024

// Function prototypes
void handleClient(int clientSocket, int *operationCount);
void reverseString(char *str);
void toUpperCase(char *str);

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int operationCount = 0;

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, BACKLOG) < 0) {
        perror("Listen failed");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // Accept a client connection
        if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen)) < 0) {
            perror("Client accept failed");
            continue;
        }

        // Handle the client connection
        handleClient(clientSocket, &operationCount);
        close(clientSocket); // Close client socket
    }

    close(serverSocket); // Close server socket
    return 0;
}

// Function to handle communication with the client
void handleClient(int clientSocket, int *operationCount) {
    char buffer[BUFFER_SIZE];
    int bytesRead;

    // Send a welcome message to the client
    const char *welcomeMsg = "Welcome to the String Operation Server!\n"
                             "Send 'REVERSE <string>' to reverse a string\n"
                             "Send 'UPPER <string>' to convert a string to uppercase\n";
    send(clientSocket, welcomeMsg, strlen(welcomeMsg), 0);

    // Read and process client messages
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0'; // Null-terminate the string
        printf("Received: %s\n", buffer);

        // Increment the operation count
        (*operationCount)++;

        // Process the command
        if (strncmp(buffer, "REVERSE ", 8) == 0) {
            reverseString(buffer + 8);
            send(clientSocket, buffer + 8, strlen(buffer + 8), 0);
        } else if (strncmp(buffer, "UPPER ", 6) == 0) {
            toUpperCase(buffer + 6);
            send(clientSocket, buffer + 6, strlen(buffer + 6), 0);
        } else {
            const char *errorMsg = "Invalid command. Use 'REVERSE <string>' or 'UPPER <string>'.\n";
            send(clientSocket, errorMsg, strlen(errorMsg), 0);
        }
        
        // Send operation count to the client
        char countMsg[100];
        snprintf(countMsg, sizeof(countMsg), "\nNumber of operations performed: %d\n", *operationCount);
        send(clientSocket, countMsg, strlen(countMsg), 0);
    }

    if (bytesRead < 0) {
        perror("Recv failed");
    }
}

// Function to reverse a string in place
void reverseString(char *str) {
    char temp;
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Function to convert a string to uppercase
void toUpperCase(char *str) {
    while (*str) {
        *str = toupper((unsigned char) *str);
        str++;
    }
}

