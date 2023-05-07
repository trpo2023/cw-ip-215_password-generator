SRCS := $(shell find . -type f -name '*.c')
HDRS := $(shell find . -type f -name '*.h')

format:
	clang-format -i $(SRCS) $(HDRS)