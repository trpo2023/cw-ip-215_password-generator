// CHECKING THE AVAILABILITY OF memcpy_s() IN THE GCC COMPILER FROM
// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/memcpy-s-wmemcpy-s crt_memcpy_s.c Copy memory in a
// more secure way.

#include <memory.h>
#include <stdio.h>

int main()
{
    int a1[10], a2[100], i;
    errno_t err;

    // Populate a2 with squares of integers
    for (i = 0; i < 100; i++)
    {
        a2[i] = i * i;
    }

    // Tell memcpy_s to copy 10 ints (40 bytes), giving
    // the size of the a1 array (also 40 bytes).
    err = memcpy_s(a1, sizeof(a1), a2, 10 * sizeof(int));
    if (err)
    {
        printf("Error executing memcpy_s.\n");
    }
    else
    {
        for (i = 0; i < 10; i++)
            printf("%d ", a1[i]);
    }
    printf("\n");
}