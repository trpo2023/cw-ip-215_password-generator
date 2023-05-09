/*
 * В РАЗРАБОТКЕ
 * https://habr.com/ru/companies/securitycode/articles/237695/
 * тест на проверку качества генерации псевдослучайных чисел
 */

#include <immintrin.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const int RD_KEY = 32;
const int NUM = 5000;

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
        exit(1); // останавливает выполнение программы полностью
    }
}

int main()
{
    double numb = 0, f_result;

    int arr[RD_KEY];   // объявление массива
    double result = 0; // инициализация переменной для хранения результата
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
                return 1; // если элемент не является 0 или 1, выходим с ошибкой
            }
            if (arr[i] == 1)
            {
                result += 1; // если элемент - 1, увеличиваем результат на 1
            }
            else
            {
                result -= 1; // если элемент - 0, уменьшаем результат на 1
            }
        }

        result = abs(result) / sqrt(RD_KEY);
        printf("S_obs: %f\n", result);
        result = erfc(result);
        printf("P_value: %f\n", result);

        if (result < 0.01)
        {
            printf("ОШИБКА\n\n");
            err_count++;
        }
    }
    printf("-------------------------------\nКоличество ошибок: %d из %i.", err_count, NUM);

    err_count = 100 * err_count / NUM;
    printf("\nШанс ошибки: %d процента(ов).\n", err_count);

    return 0;
}
