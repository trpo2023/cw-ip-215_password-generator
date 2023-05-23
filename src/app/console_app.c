#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comparison.h"
#include "convert_to_UTF8.h"
#include "fortuna.h"
#include "rdrand_support.h"

// Содержит в себе флаги типов символов для масок
typedef struct
{
    int numbers;
    int capital_letters;
    int lowercase_letters;
    int symbols;
} generation_parameters;

int main(int argc, char *argv[])
{
    // Проверка поддержки процессором инструкции rdrand
    bool program_support = rdrand_support();
    if (!program_support)
    {
        printf("Данный процессор не совместим с этой программой!\n");
        return 1;
    }

    if (argc > 1 && strcmp(argv[1], "-ctest") == 0)
    {
        printf("Программа запустилась");
        return 0;
    }

    // Объявление переменных структуры для маски
    generation_parameters parameters;

    parameters.numbers = 1;
    parameters.capital_letters = 1;
    parameters.lowercase_letters = 1;
    parameters.symbols = 1;

    int SIZEPASSWORD;

    printf("Введите количество символов в пароле: ");
    scanf("%i", &SIZEPASSWORD);
    printf("\n");

    if (SIZEPASSWORD <= 0)
    {
        printf("Ошибка! Введите корректное значение. \n");
        return 0;
    }

    printf("Использовать цифры? (0/1)\n");
    scanf("%i", &parameters.numbers);
    printf("\n");

    if (parameters.numbers != 0 && parameters.numbers != 1)
    {
        printf("Ошибка! Введите 1 или 0. \n");
        return 0;
    }

    printf("Использовать заглавные буквы? (0/1)\n");
    scanf("%i", &parameters.capital_letters);
    printf("\n");

    if (parameters.capital_letters != 0 && parameters.capital_letters != 1)
    {
        printf("Ошибка! Введите 1 или 0. \n");
        return 0;
    }

    printf("Использовать строчные буквы? (0/1)\n");
    scanf("%i", &parameters.lowercase_letters);
    printf("\n");

    if (parameters.lowercase_letters != 0 && parameters.lowercase_letters != 1)
    {
        printf("Ошибка! Введите 1 или 0.");
        return 0;
    }

    printf("Использовать символы? (0/1)\n");
    scanf("%i", &parameters.symbols);
    printf("\n");

    if (parameters.symbols != 0 && parameters.symbols != 1)
    {
        printf("Ошибка! Введите 1 или 0. \n");
        return 0;
    }
    if (parameters.numbers == 0 && parameters.capital_letters == 0 && parameters.lowercase_letters == 0 &&
        parameters.symbols == 0)
    {
        printf("Ошибка! Отсутствуют параметры для генерации пароля. \n");
        return 0;
    }
    unsigned char generated_values[SIZEPASSWORD];
    unsigned char generated_byte = 0;

    for (int i = 0; i < SIZEPASSWORD; i++)
    {
        // Генератор случайных битов с использованием маски
        while (generated_byte == 0)
        {
            generated_byte = fortuna();
            comparison(&generated_byte, parameters.numbers, parameters.capital_letters, parameters.lowercase_letters,
                       parameters.symbols);
        }

        // Конвертация в символы
        unsigned char *result = convert_to_UTF8(generated_byte);
        generated_values[i] = *result;
        printf("%s", result);

        // Проверка на повторяющиеся символы
        if (i != 0)
        {
            while (generated_values[i - 1] == generated_values[i])
            {
                while (generated_byte == 0 || generated_byte == generated_values[i - 1])
                {
                    generated_byte = fortuna();
                    comparison(&generated_byte, parameters.numbers, parameters.capital_letters,
                               parameters.lowercase_letters, parameters.symbols);
                }

                // Конвертация в символы
                unsigned char *result = convert_to_UTF8(generated_byte);
                generated_values[i] = *result;

                // Очистка памяти после выполнения программы
                free(result);
            }
        }

        // Очистка памяти после выполнения программы
        free(result);

        // Генерация нового байта для следующей итерации
        generated_byte = 0;
    }
    printf("\n");

    return 0;
}