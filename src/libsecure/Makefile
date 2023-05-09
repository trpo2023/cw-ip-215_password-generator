all: libsecure.a

libsecure.a: memcpy_s.o
	ar rcs $@ $^

memcpy_s.o: memcpy_s.c memcpy_s.h
	$(CC) -c $< -o $@

clean:
	rm -rf memcpy_s.o
	rm -rf libsecure.a