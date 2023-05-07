# параметр компиляции "-march=native" позволяет использовать все доступные инструкции процессора
CC = gcc

rdrand: rdrand.c
	$(CC) -march=native rdrand.c -o rdrand

rdrand_support: rdrand_support.c
	$(CC) -march=native rdrand_support.c -o rdrand_support

terminal_parametrs: terminal_parametrs.c
	$(CC) terminal_parametrs.c -o terminal_parametrs

rdrand_key: rdrand_key.c
	$(CC) -march=native rdrand_key.c -o rdrand_key