#include <stdbool.h>
#include <stdio.h>

#include "fortuna.h"
#include "rdrand.h"
#include "rdrand_support.h"

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
    for (int i = 0; i < 16; i++)
    {
        random_numbers[i] = rdrand();
        // printf("%i\n", random_numbers[i]);
    }

    // Поточный шифр
    int output_chacha[16];           // Целые длинные числа, сгенерированные CC20
    unsigned char result_chacha[16]; // Числа CC20, конвертированные в биты
    chacha20_20(random_numbers, output_chacha);
    for (int i = 0; i < 16; i++)
    {
        result_chacha[i] = (unsigned char)output_chacha[i] % 256;
        printf("%i\n", result_chacha[i]);
    }

    // Генератор псевдослучайных чисел
    
    // сюда вставить код для фортуны

    // Объявление переменных структуры для маски
    // generation_parameters parameters;

    // parameters.numbers = 1;
    // parameters.capital_letters = 1;
    // parameters.lowercase_letters = 1;
    // parameters.symbols = 1;
    // Вызываем фортуну, в фортуне вызывается chacha20, полученный байт отправляется на проверку в copmarison
    //  для comparison пользователь вводит параметры NUMB, BIG_LETTERS, MINI_LETTERS, SYMB
    // потом convert_into_hex а затем в convert_to_utf_8, и из этой функции у нас получается один символ
    /*
    int SIZEPASSWORD, NUMB, BIG_LETTERS, MINI_LETTERS, SYMB;
    printf("Введите количество символов в пароле");
    scanf("%i ", SIZEPASSWORD);
    printf("Использовать цифры? 0/1");
    scanf("%i ", NUMB);
    printf("Использовать КАПС? 0/1");
    scanf("%i ", BIG_LETTERS);
    printf("Использовать строчные буквы? 0/1");
    scanf("%i ", MINI_LETTERS);
    printf("Использовать символы? 0/1");
    scanf("%i ", SYMB);

    for(int i = 0; i < SIZEPASSWORD; i++)
    {

    */
    return 0;
}