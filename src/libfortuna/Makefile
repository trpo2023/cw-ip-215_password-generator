CFLAGS = -Wall -Wextra -Werror

# lib - библиотеки, main - основная прогшрамма

all: main

main: main.o libchacha20.a
	$(CC) $(CFLAGS) -o $@ $^

libchacha20.a: chacha20.o
	ar rcs $@ $^

chacha20.o: chacha20.c chacha20.h
	$(CC) -c $(CFLAGS) $< -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@