#include <immintrin.h> // нужно для RdRand
#include <stdio.h>     // для printf()

int main()
{
    unsigned int rand_num; // переменная для случайного числа
    int success;           // флаг успеха операции

    success = _rdrand32_step(&rand_num); // процессорная инструкция RdRand, генерирующая число при помощи генератора
                                         // случпйных чисел в процессоре

    // при выполненной генерации, выводим число иначе сообщение об ошибке
    if (success)
    {
        printf("%u\n", rand_num); // выводим результат генерации ("% 10" задаёт однозначное число)
        return 0;
    }
    else
    {
        printf("Generation failed.\n"); // в случае проблем выводим сообщение об ошибке
        return 1;
    }
}
