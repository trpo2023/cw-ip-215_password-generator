
#include "rdrand.h"
#include "rdrand_support.h"

#include <stdio.h>

const int RD_KEY = 1;

int main()
{
    int a = rdrand_support();
    printf("%i\n", a);
    int arr[RD_KEY];

    for (int i = 0; i < RD_KEY; i++)
    {
        arr[i] = rdrand();
    }

    for (int i = 0; i < RD_KEY; i++)
    {
        printf("%d\n", arr[i]);
    }
    printf("\n");

    return 0;
}
