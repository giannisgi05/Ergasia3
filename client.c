#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "eshop.h"

#define PORT 8080
#define SERVER_IP "127.0.0.1"

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    // Δημιουργία socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Ρύθμιση server διεύθυνσης
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Σύνδεση στον server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        int product_id = rand() % CATALOG_SIZE;
        send_order(client_socket, "Client", product_id);
        sleep(1);
    }

    close(client_socket);
    return 0;
}
