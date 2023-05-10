#include "rdrand.h"

#include <immintrin.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * RdRand - процессорная инструкция, генерирующая псевдослучайное число при помощи аппаратных стредств
 * (процессорная инструкция)
 */

int rdrand()
{
    unsigned int rand_num;
    bool success;

    success = labs(_rdrand32_step(&rand_num));

    if (success)
        return rand_num;
    else
        return 1;
}