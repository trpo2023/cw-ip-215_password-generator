// #include "comparison.h"

#include <string.h>

const char *comparison(const char *BYTE, const char PARAMETER)
{
    if (PARAMETER == 0)
    {
        const char *mask[] = {"21", "23", "24", "25", "26", "30", "31", "32", "33", "34", "35", "36", "37", "38",
                              "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c",
                              "4d", "4e", "4f", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a",
                              "5e", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d",
                              "6e", "6f", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a"};
        int mask_sz = sizeof(mask) / sizeof(*mask);

        for (int num_of_mask_element = 0; num_of_mask_element < mask_sz; num_of_mask_element++)
            if (strcmp(BYTE, mask[num_of_mask_element]) == 0)
                return BYTE;
        return NULL;
    }
    if (PARAMETER == 1)
    {
        const char *mask[] = {"21", "23", "24", "25", "26", "32", "33", "34", "35", "36", "37", "38", "39",
                              "40", "41", "42", "43", "44", "45", "46", "47", "48", "4a", "4b", "4c", "4d",
                              "4e", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a", "5e",
                              "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6d", "6e",
                              "6f", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a"};
        int mask_sz = sizeof(mask) / sizeof(*mask);

        for (int num_of_mask_element = 0; num_of_mask_element < mask_sz; num_of_mask_element++)
            if (strcmp(BYTE, mask[num_of_mask_element]) == 0)
                return BYTE;
        return NULL;
    }
}
#include <stdio.h>

int main()
{
    char *BYTE = "30";

    const char *result = comparison(BYTE, 0);

    printf("\n%s\n\n", result);
}
