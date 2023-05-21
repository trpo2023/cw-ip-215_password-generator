CC = gcc
CFLAGS = -march=native -Wall -Wextra -Werror
LDFLAGS =

SRCS = main.c rdrand_support.c rdrand.c chacha20.c fortuna.c
OBJS = $(SRCS:.c=.o)
TARGET = main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
