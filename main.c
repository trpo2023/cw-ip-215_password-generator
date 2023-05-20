#include <stdbool.h>
#include <stdio.h>

#include "rdrand.h"
#include "rdrand_support.h"
#include "chacha20.h"
// #include "fortuna.h"

// Содержит в себе флаги типов символов для масок
typedef struct
{
    bool numbers;
    bool capital_letters;
    bool lowercase_letters;
    bool symbols;
} generation_parameters;

// argv[0] - имя программы
// цикл (int i = 1; i < argc; ++i) с argv[i] получает параметры запуска программы
int main()
{
    // Проверка поддержки процессором инструкции rdrand
    bool program_support = rdrand_support();
    if (!program_support)
        return 1;

    // Генерация псевдослучайных чисел
    int random_numbers[16];
    for (int i; i < 16; i++)
    {
        random_numbers[i] = rdrand();
        printf("RdRand: %i\n", random_numbers[i]);
    }

    // Поточный шифр
    int result_chacha[16];
    chacha20_20(random_numbers, result_chacha);
    for (int i; i < 16; i++)
    {
        printf("ChaCha: %i\n", result_chacha[i]);
    }

    // Генератор псевдослучайных чисел
    // fortuna();

    // Объявление переменных структуры
    // generation_parameters parameters; 

    // parameters.numbers = 1;
    // parameters.capital_letters = 1;
    // parameters.lowercase_letters = 1;
    // parameters.symbols = 1;

    return 0;
}