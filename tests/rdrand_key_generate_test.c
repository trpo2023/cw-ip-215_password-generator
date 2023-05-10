/*
 * В РАЗРАБОТКЕ
 * https://habr.com/ru/companies/securitycode/articles/237695/
 * тест на проверку качества генерации псевдослучайных чисел
 *
 * РЕЗУЛЬТАТЫ:
 * AMD RYZEN 5500U 5% (53.746 / 1.000.000)
 */

#include <immintrin.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TERMINAL_RED "\x1B[31m"
#define TERMINAL_GREEN "\x1B[32m"
#define TERMINAL_RESET "\x1B[0m"

const int RD_KEY = 32;
const int NUM = 1000000;

int rdrand()
{
    unsigned int rand_num;
    int success;

    success = _rdrand32_step(&rand_num);

    if (success)
    {
        return rand_num % 2; // генерация двоичного числа
    }
    else
    {
        printf("Generation failed.\n");
        exit(1);
    }
}

int main()
{
    double numb = 0, f_result;

    int arr[RD_KEY];
    double result = 0;
    int err_count = 0;

    for (int a = 0; a < NUM; a++)
    {
        for (int i = 0; i < RD_KEY; i++)
        {
            arr[i] = rdrand();

            // printf("%i", arr[i]);

            if (arr[i] != 0 && arr[i] != 1)
            { // проверка, что элемент является 0 или 1
                fprintf(stderr, "Error! Invalid key: %i. %d\n", i, arr[i]);
                return 1; // если элемент не является 0 или 1 -  ошибка
            }
            if (arr[i] == 1)
                result += 1; // если элемент - 1, увеличиваем результат на 1
            else
                result -= 1; // если элемент - 0, уменьшаем результат на 1
        }

        result = abs(result) / sqrt(RD_KEY);
        printf("S_obs: %f\n", result);
        result = erfc(result);
        printf("P_value: %f\n", result);

        if (result < 0.01)
        {
            printf("%sОШИБКА%s\n\n", TERMINAL_RED, TERMINAL_RESET);
            err_count++;
        }
        else
            printf("%sТест пройден%s\n\n", TERMINAL_GREEN, TERMINAL_RESET);
    }
    printf("-------------------------------\nКоличество ошибок: %d из %i.", err_count, NUM);

    err_count = 100 * err_count / NUM;
    printf("\nШанс ошибки: %d процента(ов).\n", err_count);

    return 0;
}
