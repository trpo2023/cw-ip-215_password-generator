CC = gcc
CFLAGS = -march=native -Wall -Wextra -Werror

TARGET = pwgen_app
TESTTARGET = tests_app

ALLLIBS = -I $(APPDIR) -I $(RDRNDDIR) -I $(CC20DIR) -I $(FRTNDIR) -I $(CMPRRDIR) -I $(CNVRTDIR)

# DIRECTORY PATHS
APPDIR   = src/app
RDRNDDIR = src/librdrand
CC20DIR  = src/libchacha20
FRTNDIR  = src/libfortuna
CMPRRDIR = src/libcomparison
CNVRTDIR = src/libconvert

.PHONY: all dir format clean test

all: dir bin/$(TARGET)

# BUILDING AN APPLICATION
bin/$(TARGET): bin/$(APPDIR)/console_app.o bin/$(RDRNDDIR)/rdrand_support.o bin/$(RDRNDDIR)/rdrand.o bin/$(CC20DIR)/chacha20.o bin/$(FRTNDIR)/fortuna.o bin/$(CMPRRDIR)/comparison.o bin/$(CNVRTDIR)/convert_to_UTF8.o
	$(CC) $(CFLAGS) $^ -o $@

bin/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ $(ALLLIBS)

# CREATE DIRECTORIES
dir:
	mkdir -p bin/$(APPDIR)
	mkdir -p bin/$(RDRNDDIR)
	mkdir -p bin/$(CC20DIR)
	mkdir -p bin/$(FRTNDIR)
	mkdir -p bin/$(CMPRRDIR)
	mkdir -p bin/$(CNVRTDIR)

# FORMATTING THROUGH CLANG-FORMAT
SRCS := $(shell find . -type f -name "*.c")
HDRS := $(shell find . -type f -name "*.h")

format:
	clang-format -i $(SRCS) $(HDRS)

# CLEANING ALL COMPILER BUILD ARTIFACTS AND BINARIES
clean:
	rm -f $(TARGET) $(CLNA)
	rm -rf bin/

CLNA := $(shell find . -type f -name "*.o")

# BUILDING TESTS
test: dir bin/$(TARGET) bin/$(TESTTARGET)

bin/$(TESTTARGET): bin/test/main.o bin/test/tests.o bin/$(RDRNDDIR)/rdrand.o bin/$(FRTNDIR)/fortuna.o bin/$(CC20DIR)/chacha20.o bin/$(CMPRRDIR)/comparison.o bin/$(CNVRTDIR)/convert_to_UTF8.o
	$(CC) $(CFLAGS) $^ -o $@ -lm $(ALLLIBS)
	cd bin/ && ./$(TESTTARGET)

bin/%.o: %.c
	mkdir -p bin/test
	$(CC) -c $(CFLAGS) $< -o $@ -lm -I thirdparty $(ALLLIBS)