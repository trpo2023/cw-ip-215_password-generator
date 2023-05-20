#include "rdrand_support.h"

#include <cpuid.h>

/*
 * Осуществление проверки наличия процессорной инструкции для RdRand
 */

int rdrand_support()
{
    unsigned int eax = 1, ebx, ecx = 0, edx;

    __cpuid(1, eax, ebx, ecx, edx);
    int rdrand_support_value = (ecx & 0x40000000) ? 1 : 0;

    return rdrand_support_value;
}