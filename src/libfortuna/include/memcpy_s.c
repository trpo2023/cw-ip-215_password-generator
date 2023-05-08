#include <string.h>

void memcpy_s(void *dest, size_t dest_size, const void *src, size_t n) {
    if (n > dest_size) {
        // Обработка ошибки - размер буфера назначения меньше, чем требуемый размер копирования
        return;
    }
    memcpy(dest, src, n);
}
