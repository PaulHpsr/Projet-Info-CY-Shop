all: main

CC = gcc
override CFLAGS += -g -Wno-everything -pthread -lm -lncursesw

##ajout pour compiler les fichier de src directement
SRCS = $(wildcard *.c)
HEADERS = $(wildcard *.h)

main: $(SRCS) $(HEADERS)
    $(CC) -o "$@" $(SRCS) $(CFLAGS)

clean:
    rm -f main
