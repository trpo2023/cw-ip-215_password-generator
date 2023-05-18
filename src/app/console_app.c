#include <stdio.h>
/*
 * Генерация числа с помощью всех функций программы
 * argv - имя программы, для получения можно использовать argv[0]
 *
 * цикл (int i = 1; i < argc; ++i) с arg[i] получает параметры запуска программы
 */
int main(int argc, char *argv[])
{

    fortuna_state_t state;
    fortuna_init(&state);
    unsigned char output[GENERATE_SIZE];
    fortuna_generate(&state, output, GENERATE_SIZE);

    int i;
    for (i = 0; i < GENERATE_SIZE; i++)
    {
        printf(" %x", output[i]);
    }
    printf("\n");
}