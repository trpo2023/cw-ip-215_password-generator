#include <cpuid.h>
#include <stdio.h>

int rdrand_support() {
    unsigned int eax, ebx, ecx, edx;
    eax = 1;
    ecx = 0;
    __cpuid(1, eax, ebx, ecx, edx);
    int rdrand_support_value = (ecx & 0x40000000) ? 1 : 0; // если инструкция поддерживается, то присваивает rdrand_support_value значение 1, иначе 0
}
