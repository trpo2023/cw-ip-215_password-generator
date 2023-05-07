all: rdrand_key_test

rdrand_key_test: rdrand_key_test.c
	gcc -march=native rdrand_key_test.c -o rdrand_key_test -lm

run:
	./rdrand_key_test