# ФЛАГ "-c" КОМПИЛИРУЕТ ФАЙЛЫ В .o ФАЙЛЫ
# ФЛАГ "-march=native" 

# COMPILER SETTINGS
CC = gcc
CFLAGS = -march=native -Wall -Wextra -Werror

SRCS := $(shell find . -type f -name '*.c')
HDRS := $(shell find . -type f -name '*.h')

# BUILDING APPLICATION
all: bin/console_app.exe

bin/console_app.exe: src/app/console_app.a # СЮДА ВСТАВИТЬ ВСЕ БИБЛИОТЕКИ ДЛЯ КОМПИЛЯЦИИ ПРОГРАММЫ
	$(CC) $(CFLAGS) $< -o $@

bin/src/app/console_app.a: src/app/console_app.c

# BYTES WORK LIBRARIES (UTF-8 TOOLS)
bin/src/libbyteswork/libbyteswork.a: bin/src/libbyteswork/comparison.o bin/src/libbyteswork/convert_into_hex.o bin/src/libbyteswork/convert_to_utf_8.o
	ar rcs $@ $^

bin/src/libbyteswork/comparison.o: src/libbyteswork/comparison.c src/libbyteswork/comparison.h
	$(CC) -c $(CFLAGS) $< -o $@

bin/src/libbyteswork/convert_into_hex.o: src/libbyteswork/convert_into_hex.c src/libbyteswork/convert_into_hex.h
	$(CC) -c $(CFLAGS) $< -o $@

bin/src/libbyteswork/convert_to_utf_8.o: src/libbyteswork/convert_to_utf_8.c src/libbyteswork/convert_to_utf_8.h
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -c $(CFLAGS) $< -o $@

# CHACHA20 LIBRARIES
bin/src/libchacha20/chacha20.a: bin/src/libchacha20/chacha20.o
	ar rcs $@ $^

bin/src/libchacha20/chacha20.o: src/libchacha20/chacha20.c src/libchacha20/chacha20.h
	$(CC) -c $(CFLAGS) $< -o $@

# FORTUNA LIBRARIES
bin/src/libfortuna/libfortuna.a: bin/src/libfortuna/fortuna.o
	ar rcs $@ $^

bin/src/libfortuna/fortuna.o: src/libfortuna/fortuna.c src/libfortuna/fortuna.h
	$(CC) -c $(CFLAGS) $< -o $@

# RDRAND LIBRARIES
bin/src/librdrand/librdrand.a: bin/src/librdrand/rdrand.o bin/src/librdrand/rdrand_support.o
	ar rcs $@ $^

bin/src/librdrand/rdrand.o: src/librdrand/rdrand.c src/librdrand/rdrand.h
	$(CC) -c $(CFLAGS) $< -o $@

bin/src/librdrand/rdrand_support.o: src/librdrand/rdrand_support.c src/librdrand/rdrand_support.h
	$(CC) -c $(CFLAGS) $< -o $@

# SECURE LIBRARIES
bin/src/libsecure/libsecure.a: bin/src/libsecure/memcpy_s.o bin/src/libsecure/memset_s.o
	ar rcs $@ $^

bin/src/libsecure/memcpy_s.o: src/libsecure/memcpy_s.c src/libsecure/memcpy_s.h
	$(CC) -c $(CFLAGS) $< -o $@

bin/src/libsecure/memset_s.o: src/libsecure/memset_s.c src/libsecure/memset_s.h
	$(CC) -c $(CFLAGS) $< -o $@

# CONSOLE LIBRARIES
bin/src/libconsole/libconsole.a: bin/src/libconsole/set_up_run.o
	ar rcs $@ $^

bin/src/libconsole/set_up_run.o: src/libconsole/set_up_run.c src/libconsole/set_up_run.h
	$(CC) -c $(CFLAGS) $< -o $@

# FORMATTING THROUGH CLANG-FORMAT
format:
	clang-format -i $(SRCS) $(HDRS)

# CLEANING ALL COMPILER BUILD ARTIFACTS AND BINARIES
clean:
	rm -rf