#include <stdbool.h>
#include <stdio.h>

#include "fortuna.h"
#include "rdrand_support.h"
#include "comparison.h"

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

    // Объявление переменных структуры для маски
    generation_parameters parameters;

    parameters.numbers = 1;
    parameters.capital_letters = 1;
    parameters.lowercase_letters = 1;
    parameters.symbols = 1;

    unsigned char fortuna_output;

    // Вызов генератора псевдослучайных чисел
    while (fortuna_output == 0)
    {
        fortuna_output = fortuna();
        printf("%x ", fortuna_output);
        comparison(&fortuna_output, parameters.numbers, parameters.capital_letters, parameters.lowercase_letters,
                   parameters.symbols);
    }
    printf("%x ", fortuna_output);

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