#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "eshop.h"

void init_catalog(Product *catalog) {
    for (int i = 0; i < CATALOG_SIZE; i++) {
        snprintf(catalog[i].description, sizeof(catalog[i].description), "Product-%d", i);
        catalog[i].price = (i + 1) * 10;
        catalog[i].item_count = 2; // 2 διαθέσιμα προϊόντα ανά τύπο
    }
}

void handle_client(int client_socket, Product *catalog) {
    char buffer[1024];
    while (read(client_socket, buffer, sizeof(buffer)) > 0) {
        int product_id;
        char client_name[50];

        sscanf(buffer, "%s %d", client_name, &product_id);

        if (product_id >= 0 && product_id < CATALOG_SIZE) {
            if (catalog[product_id].item_count > 0) {
                catalog[product_id].item_count--;
                snprintf(buffer, sizeof(buffer), "Order successful: %s bought %s for %d EUR\n",
                         client_name, catalog[product_id].description, catalog[product_id].price);
            } else {
                snprintf(buffer, sizeof(buffer), "Order failed: %s not available\n",
                         catalog[product_id].description);
            }
        } else {
            snprintf(buffer, sizeof(buffer), "Invalid product ID\n");
        }

        write(client_socket, buffer, strlen(buffer));
        memset(buffer, 0, sizeof(buffer));
    }

    close(client_socket);
}
