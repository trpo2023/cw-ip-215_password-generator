
#include "rdrand_key.h"
#include "rdrand_support.h"

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
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}
