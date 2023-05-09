CC = gcc
CFLAGS = # -Wall -Wextra -Werror

all: fortuna

fortuna: fortuna.o libsecure.a
	$(CC) $(CFLAGS) -o $@ $^

fortuna.o: fortuna.c
	$(CC) -c $(CFLAGS) $< -o $@

run:
	./fortuna

clean:
	rm -rf fortuna
	rm -rf fortuna.o
	rm -rf libsecure.a