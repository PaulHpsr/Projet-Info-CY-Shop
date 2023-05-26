all: main

CC = gcc
override CFLAGS += -g -Wno-everything -pthread -lm -lncursesw

##ajout pour compiler les fichier de src directement
DIR_SRC = src/
DIR_INC = src/
SRCS = $(wildcard $(DIR_SRC)*.c)
HEADERS = $(wildcard $(DIR_INC)*.h)


main: $(SRCS) $(HEADERS)
    $(CC) -o "$@" $(SRCS)    $(CFLAGS)

clean:
    rm -f main main-debug
