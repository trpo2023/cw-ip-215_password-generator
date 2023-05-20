#include "comparison.h"
#include "fortuna.c"

#include <stdbool.h>
#include <stdio.h>
/*
 * Генерация числа с помощью всех функций программы
 * argv - имя программы, для получения можно использовать argv[0]
 *
 * цикл (int i = 1; i < argc; ++i) с arg[i] получает параметры запуска программы
 */
int main(int argc, char *argv[])
{
    char BYTE, NUMB, BIG_LETTERS, MINI_LETTERS, SYMB;
    unsigned char output[GENERATE_SIZE];
    int i;

    printf("\n Введите параметры: цифры, заглавные буквы, строчные буквы, символы \n");
    scanf("%c %c %c %c ", &NUMB, &BIG_LETTERS, &MINI_LETTERS, &SYMB);
    bool flagend = false;
    while (flagend != true)
    {
        fortuna_struct state;
        fortuna_init(&state);
        unsigned char output[GENERATE_SIZE];
        fortuna_generate(&state, output, GENERATE_SIZE);
        
            for (i = 0; i < GENERATE_SIZE; i++)
            {
                BYTE = output[i];
                if (comparison(BYTE, NUMB, BIG_LETTERS, MINI_LETTERS, SYMB) != NULL)
                {
                    flagend = 1;
                    convert_into_hex(BYTE);
                    // Конвертация байта в символ
                }
            }
    }
    int i;
    for (i = 0; i < GENERATE_SIZE; i++)
    {
        printf(" %x", output[i]);
    }
    printf("\n");
}

/*
const char NUMB, BIG_LETTERS, MINI_LETTERS, SYMB;
    char *BYTE = "30";
    bool flag;
    scanf("%i %i %i %i ", NUMB, BIG_LETTERS, MINI_LETTERS, SYMB);

    const char *result = comparison(BYTE, NUMB, BIG_LETTERS, MINI_LETTERS, SYMB);

    printf("\n%s\n\n", result);

    return 0;

    int i;
    if (GENERATE_SIZE == 1)
        return output[0];
    else
        for (i = 0; i < GENERATE_SIZE; i++)
            return output[i];
*/