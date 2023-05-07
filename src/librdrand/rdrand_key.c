#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

const int RD_KEY = 10;

int rdrand()
{
    unsigned int rand_num;
    int success;

    success = _rdrand32_step(&rand_num);

    if (success)
    {
        return rand_num;
    }
    else
    {
        printf("Generation failed.\n");
        exit(1);
    }
}

int main()
{
    int arr[RD_KEY];

    for (int i = 0; i < RD_KEY; i++)
    {
        arr[i] = rdrand();
    }

    for (int i = 0; i < RD_KEY; i++)
    {
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}
