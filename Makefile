all: CY_SHOP_main

CC = gcc
override CFLAGS += -g -Wno-everything -pthread -lm 

##ajout pour compiler les fichier de src directement
SRCS = $(wildcard *.c)
HEADERS = $(wildcard *.h)

CY_SHOP_main: $(SRCS) $(HEADERS)
	$(CC) -o "$@" $(SRCS) $(CFLAGS)

clean:
	rm -f CY_SHOP_main
