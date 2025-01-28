#ifndef ESHOP_H
#define ESHOP_H

#define CATALOG_SIZE 20

typedef struct {
    char description[50];
    int price;
    int item_count;
} Product;

void init_catalog(Product *catalog);
void handle_client(int client_socket, Product *catalog);
void send_order(int client_socket, const char *client_name, int product_id);

#endif
