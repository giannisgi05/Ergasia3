# Makefile για το e-shop

CC = gcc
CFLAGS = -Wall -g
EXEC = server client
OBJS = server.o client.o eshop.o

all: $(EXEC)

server: server.o eshop.o
	$(CC) $(CFLAGS) -o server server.o eshop.o

client: client.o eshop.o
	$(CC) $(CFLAGS) -o client client.o eshop.o

server.o: server.c eshop.h
	$(CC) $(CFLAGS) -c server.c

client.o: client.c eshop.h
	$(CC) $(CFLAGS) -c client.c

eshop.o: eshop.c eshop.h
	$(CC) $(CFLAGS) -c eshop.c

clean:
	rm -f $(OBJS) $(EXEC)
