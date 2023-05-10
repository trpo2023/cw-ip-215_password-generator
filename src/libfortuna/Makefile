CC = gcc
CFLAGS = # -Wall -Wextra -W

all: fortuna

fortuna: fortuna.o libsecure.a
	$(CC) $(CFLAGS) -o $@ $^

fortuna.o: fortuna.c
	$(CC) -c $(CFLAGS) $< -o $@

libsecure.a: memcpy_s.o
	ar rcs $@ $^

memcpy_s.o: memcpy_s.c memcpy_s.h
	$(CC) -c $(CFLAGS) $< -o $@

run:
	./fortuna

clean:
	rm -rf fortuna
	rm -rf fortuna.o
	rm -rf libsecure.a