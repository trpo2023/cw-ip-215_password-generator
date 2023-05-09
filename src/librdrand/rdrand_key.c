#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

int rdrand()
{
    unsigned int rand_num; // переменная для случайного числа
    int success;           // флаг успеха операции

    success = _rdrand32_step(&rand_num); // процессорная инструкция RdRand, генерирующая число при помощи генератора
                                         // случайных чисел в процессоре

    if (success)
    {
        return rand_num; // возвращаем результат генерации
    }
    else
    {
        return 1; // в случае проблем возвращаем ошибку сообщение об ошибке
    }
}