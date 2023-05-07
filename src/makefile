# параметр компиляции "-march=native" позволяет использовать все доступные инструкции процессора
CC = gcc

exe_rdrand: rdrand.c
	$(CC) -march=native rdrand.c -o exe_rdrand

exe_rdrand_support: rdrand_support.c
	$(CC) -march=native rdrand_support.c -o exe_rdrand_support