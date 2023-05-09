# -march=native - необходим для процессорной инструкции RdRand

CC = gcc
CFLAGS = -march=native -Wall -Wextra -Werror

all: EXAMPLE_OF_USE

EXAMPLE_OF_USE: EXAMPLE_OF_USE.o librdrand.a
	$(CC) $(CFLAGS) -o $@ $^

librdrand.a: rdrand_key.o rdrand_support.o
	ar rcs $@ $^

rdrand_key.o: rdrand_key.c rdrand_key.h
	$(CC) -c $(CFLAGS) $< -o $@ 

rdrand_support.o: rdrand_support.c rdrand_support.h
	$(CC) -c $(CFLAGS) $< -o $@

EXAMPLE_OF_USE.o: EXAMPLE_OF_USE.c
	$(CC) -c $(CFLAGS) $< -o $@

run:
	./EXAMPLE_OF_USE

clean:
	rm -rf librdrand.a
	rm -rf EXAMPLE_OF_USE
	rm -rf EXAMPLE_OF_USE.o
	rm -rf rdrand_key.o
	rm -rf rdrand_support.o