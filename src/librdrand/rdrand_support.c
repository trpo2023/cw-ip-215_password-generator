#include <cpuid.h> // нужно для процессорных инструкций

int rdrand_support()
{
    unsigned int eax, ebx, ecx, edx;
    eax = 1; // запрос информации о процессоре
             // (https://en.wikipedia.org/wiki/CPUID#EAX=1:_Processor_Info_and_Feature_Bits)
    ecx = 0; // значение поддержки RdRand
    __cpuid(1, eax, ebx, ecx, edx); // возвращает информацию о возможностях процессора в eax, ebx, ecx, edx
    int rdrand_support_value =
        (ecx & 0x40000000) ? 1 : 0; // если инструкция поддерживается (проверка путём сравнения бита 30 регистра), то
                                    // присваивает rdrand_support_value значение 1, иначе 0
    return rdrand_support_value;
}