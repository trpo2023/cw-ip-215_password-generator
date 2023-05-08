CC = gcc
CFLAGS = # -Wall -Wextra -Werror
LIB_PATH = include

# lib - библиотеки, main - основная прогшрамма

all: fortuna

fortuna: fortuna.o include/libmemcpy_s.a
	$(CC) $(CFLAGS) -o $@ $^

fortuna.o: fortuna.c
	$(CC) -c $(CFLAGS) $< -o $@ -I $(LIB_PATH) 

include/libmemcpy_s.a: include/memcpy_s.o
	ar rcs $@ $^

include/memcpy_s.o: include/memcpy_s.c include/memcpy_s.h
	$(CC) -c $(CFLAGS) $< -o $@ -I $(LIB_PATH)