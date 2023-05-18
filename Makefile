# ФЛАГ "-c" КОМПИЛИРУЕТ ФАЙЛЫ В "*.o" ФАЙЛЫ
# ФЛАГ "-march=native" 

# COMPILER SETTINGS
CC = gcc
CFLAGS = -march=native -Wall -Wextra -Werror

# DIRECTORY PATHS
LIBAPP = src/app
LIBWRK = src/libbyteswork
LIBCC2 = src/libchacha20
LIBFRT = src/libfortuna
LIBRDR = src/librdrand
LIBSCR = src/libsecure

# CREATE DIRECTORIES
dir:
	mkdir -p bin/$(LIBAPP)
	mkdir -p bin/$(LIBWRK)
	mkdir -p bin/$(LIBCC2)
	mkdir -p bin/$(LIBFRT)
	mkdir -p bin/$(LIBRDR)
	mkdir -p bin/$(LIBSCR)

all: dir app

# BUILDING APPLICATION
app: bin/console_app

bin/console_app: bin/$(LIBSCR)/libsecure.a bin/$(LIBRDR)/librdrand.a bin/$(LIBCC2)/chacha20.a bin/$(LIBFRT)/libfortuna.a bin/$(LIBWRK)/libbyteswork.a bin/$(LIBCSL)/libconsole.a bin/$(LIBAPP)/console_app.a  # INSERT ALL THE LIBRARIES FOR COMPILING THE PROGRAM HERE
	$(CC) $(CFLAGS) $^ -o $@

bin/$(LIBAPP)/console_app.a: $(LIBAPP)/console_app.c
	$(CC) -c $(CFLAGS) $< -o $@

# BYTES WORK LIBRARIES (UTF-8 TOOLS)
bin/$(LIBWRK)/libbyteswork.a: bin/$(LIBWRK)/comparison.o bin/$(LIBWRK)/convert_into_hex.o bin/$(LIBWRK)/convert_to_utf_8.o
	ar rcs $@ $^

bin/$(LIBWRK)/comparison.o: $(LIBWRK)/comparison.c $(LIBWRK)/comparison.h
	$(CC) -c $(CFLAGS) $< -o $@

bin/$(LIBWRK)/convert_into_hex.o: $(LIBWRK)/convert_into_hex.c $(LIBWRK)/convert_into_hex.h
	$(CC) -c $(CFLAGS) $< -o $@

bin/$(LIBWRK)/convert_to_utf_8.o: $(LIBWRK)/convert_to_utf_8.c $(LIBWRK)/convert_to_utf_8.h
	$(CC) -c $(CFLAGS) $< -o $@

# CHACHA20 LIBRARIES
bin/$(LIBCC2)/chacha20.a: bin/$(LIBCC2)/chacha20.o
	ar rcs $@ $^

bin/$(LIBCC2)/chacha20.o: $(LIBCC2)/chacha20.c $(LIBCC2)/chacha20.h
	$(CC) -c $(CFLAGS) $< -o $@

# FORTUNA LIBRARIES
bin/$(LIBFRT)/libfortuna.a: bin/$(LIBFRT)/fortuna.o
	ar rcs $@ $^

bin/$(LIBFRT)/fortuna.o: $(LIBFRT)/fortuna.c $(LIBFRT)/fortuna.h
	$(CC) -c $(CFLAGS) $< -o $@ -I $(LIBSCR) -I $(LIBRDR) -I $(LIBCC2)

# RDRAND LIBRARIES
bin/$(LIBRDR)/librdrand.a: bin/$(LIBRDR)/rdrand.o bin/$(LIBRDR)/rdrand_support.o
	ar rcs $@ $^

bin/$(LIBRDR)/rdrand.o: $(LIBRDR)/rdrand.c $(LIBRDR)/rdrand.h
	$(CC) -c $(CFLAGS) $< -o $@

bin/$(LIBRDR)/rdrand_support.o: $(LIBRDR)/rdrand_support.c $(LIBRDR)/rdrand_support.h
	$(CC) -c $(CFLAGS) $< -o $@

# SECURE LIBRARIES
bin/$(LIBSCR)/libsecure.a: bin/$(LIBSCR)/memcpy_s.o bin/$(LIBSCR)/memset_s.o
	ar rcs $@ $^

bin/$(LIBSCR)/memcpy_s.o: $(LIBSCR)/memcpy_s.c $(LIBSCR)/memcpy_s.h
	$(CC) -c $(CFLAGS) $< -o $@

bin/$(LIBSCR)/memset_s.o: $(LIBSCR)/memset_s.c $(LIBSCR)/memset_s.h
	$(CC) -c $(CFLAGS) $< -o $@

# FORMATTING THROUGH CLANG-FORMAT
SRCS := $(shell find . -type f -name "*.c")
HDRS := $(shell find . -type f -name "*.h")

format:
	clang-format -i $(SRCS) $(HDRS)

tests: bin/tests/rdrand_key_generate_test

bin/tests/rdrand_key_generate_test: tests/rdrand_key_generate_test.c
	mkdir -p bin/tests
	$(CC) $(CFLAGS) $^ -o $@ -lm
	cd bin/tests && ./rdrand_key_generate_test

# CLEANING ALL COMPILER BUILD ARTIFACTS AND BINARIES
clean:
	rm -rf bin/
# find . -type f -name "*.o" | xargs rm -rf
# find . -type f -name "*.a" | xargs rm -rf
# find . -type f -name "*.exe" | xargs rm -rf
# find bin -type d -name "lib*" | xargs rm -rf