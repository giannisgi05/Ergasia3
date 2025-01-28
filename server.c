#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "eshop.h"

#define PORT 8080
#define MAX_CLIENTS 5

int main() {
    int server_socket, client_socket, addr_len;
    struct sockaddr_in server_addr, client_addr;

    Product catalog[CATALOG_SIZE];
    init_catalog(catalog);

    // Δημιουργία socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Ρύθμιση διεύθυνσης server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Δέσμευση υποδοχής
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Έναρξη ακρόασης
    if (listen(server_socket, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d...\n", PORT);

    addr_len = sizeof(client_addr);
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&addr_len)) >= 0) {
        handle_client(client_socket, catalog);
    }

    close(server_socket);
    return 0;
}
