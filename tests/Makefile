# -lm 			- необходим для библиотеки math.h
# -march=native - необходим для процессорной инструкции RdRand

all: rdrand_key_generate_test

rdrand_key_generate_test: rdrand_key_generate_test.c
	gcc -march=native -o $@ $^ -lm

run:
	./rdrand_key_generate_test

clean:
	rm -rf rdrand_key_generate_test