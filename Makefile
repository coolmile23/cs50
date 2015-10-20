CFLAGS = -ggdb  -Wall -std=gnu99 -Werror -Wformat=0 -O0 -o main

CC = gcc

OBJ = buble_sort.o


main:$(OBJ)
	$(CC) $(CFLAGS) $(OBJ)

clean:
	rm *.o 

all: main clean
