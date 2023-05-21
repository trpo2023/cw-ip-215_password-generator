#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "fortuna.h"
#include "rdrand_support.h"
#include "comparison.h"
#include "convert_to_UTF8.h"

// Содержит в себе флаги типов символов для масок
typedef struct
{
    bool numbers;
    bool capital_letters;
    bool lowercase_letters;
    bool symbols;
} generation_parameters;

#include <stdio.h>

void printBinary(unsigned char num) {
    int i;
    for (i = 7; i >= 0; i--) {
        unsigned char mask = 1 << i;
        unsigned char bit = (num & mask) ? 1 : 0;
        printf("%d", bit);
    }
    printf("\n");
}

// argv[0] - имя программы
// цикл (int i = 1; i < argc; ++i) с argv[i] получает параметры запуска программы
int main()
{
    // Проверка поддержки процессором инструкции rdrand
    bool program_support = rdrand_support();
    if (!program_support)
        return 1;

    // Объявление переменных структуры для маски
    generation_parameters parameters;

    parameters.numbers = 1;
    parameters.capital_letters = 1;
    parameters.lowercase_letters = 1;
    parameters.symbols = 1;

    unsigned char fortuna_output;

    // Генератор случайных битов с использованием маски
    while (fortuna_output == 0)
    {
        fortuna_output = fortuna();
        comparison(&fortuna_output, parameters.numbers, parameters.capital_letters, parameters.lowercase_letters,
                   parameters.symbols);
    }

    // Конвертация в символы
    unsigned char *result = convert_to_UTF8(fortuna_output);
    printf("%s\n", result);

    // Очистка памяти после выполнения программы
    free(result);
    return 0;
}