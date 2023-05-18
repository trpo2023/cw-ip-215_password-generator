#include <stdio.h>

int main() {
    char *massive[] = {"21", "23", "0"};
    int size = (sizeof(massive) / sizeof(*massive));

    printf("Размер массива: %i\n", size);

    return 0;
}
