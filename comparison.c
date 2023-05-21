#include "comparison.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const char *comparison(const unsigned char *GEN_BYTE, const char NUMBERS, const char CAPITAL_LETTERS,
                       const char LOWERCASE_LETTERS, const char SYMBOLS)
{
    int mask_size;

    if (SYMBOLS == 1)
    {
        const char *mask[] = {"21", "23", "24", "25", "26", "30", "5e"};
        mask_size = sizeof(mask) / sizeof(*mask);

        for (int num_of_mask_element = 0; num_of_mask_element < mask_size; num_of_mask_element++)
        {
            if (strcmp((const char *)GEN_BYTE, mask[num_of_mask_element]) == 0)
                return mask[num_of_mask_element];
        }
    }

    if (NUMBERS == 1)
    {
        const char *mask[] = {"30", "31", "32", "33", "34", "35", "36", "37", "38", "39"};
        mask_size = sizeof(mask) / sizeof(*mask);

        for (int num_of_mask_element = 0; num_of_mask_element < mask_size; num_of_mask_element++)
        {
            if (strcmp((const char *)GEN_BYTE, mask[num_of_mask_element]) == 0)
                return mask[num_of_mask_element];
        }
    }

    if (CAPITAL_LETTERS == 1)
    {
        const char *mask[] = {"41", "42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c", "4d",
                              "4e", "4f", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a"};
        mask_size = sizeof(mask) / sizeof(*mask);

        for (int num_of_mask_element = 0; num_of_mask_element < mask_size; num_of_mask_element++)
        {
            if (strcmp((const char *)GEN_BYTE, mask[num_of_mask_element]) == 0)
                return mask[num_of_mask_element];
        }
    }

    if (LOWERCASE_LETTERS == 1)
    {
        const char *mask[] = {"61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d",
                              "6e", "6f", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a"};
        mask_size = sizeof(mask) / sizeof(*mask);

        for (int num_of_mask_element = 0; num_of_mask_element < mask_size; num_of_mask_element++)
        {
            if (strcmp((const char *)GEN_BYTE, mask[num_of_mask_element]) == 0)
                return mask[num_of_mask_element];
        }
    }

    return NULL;
}