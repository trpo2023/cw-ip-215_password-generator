// #include "comparison.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

const char *comparison(const char *BYTE, const char NUMB, const char BIG_LETTERS, const char MINI_LETTERS,
                       const char SYMB)
{
    // char result;

    if (NUMB == 1)
    {
        const char *mask[] = {"30", "31", "32", "33", "34", "35", "36", "37", "38", "39"};
        int mask_sz = sizeof(mask) / sizeof(*mask);

        for (int num_of_mask_element = 0; num_of_mask_element < mask_sz; num_of_mask_element++)
            if (strcmp(BYTE, mask[num_of_mask_element]) == 0)
                return BYTE;
        return NULL;
    }
    if (BIG_LETTERS == 1)
    {
        const char *mask[] = {"41", "42", "43", "44", "45", "46", "47", "48", "49", "4a", "4b", "4c", "4d",
                              "4e", "4f", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a"};
        int mask_sz = sizeof(mask) / sizeof(*mask);

        for (int num_of_mask_element = 0; num_of_mask_element < mask_sz; num_of_mask_element++)
            if (strcmp(BYTE, mask[num_of_mask_element]) == 0)
                return BYTE;
        return NULL;
    }
    if (MINI_LETTERS == 1)
    {
        const char *mask[] = {"61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6c", "6d",
                              "6e", "6f", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a"};
        int mask_sz = sizeof(mask) / sizeof(*mask);

        for (int num_of_mask_element = 0; num_of_mask_element < mask_sz; num_of_mask_element++)
            if (strcmp(BYTE, mask[num_of_mask_element]) == 0)
                return BYTE;
        return NULL;
    }
    if (SYMB == 1)
    {
        const char *mask[] = {"21", "23", "24", "25", "26", "30", "5e"};
        int mask_sz = sizeof(mask) / sizeof(*mask);

        for (int num_of_mask_element = 0; num_of_mask_element < mask_sz; num_of_mask_element++)
            if (strcmp(BYTE, mask[num_of_mask_element]) == 0)
                return BYTE;
        return NULL;
    }
    return 0;
}

// const char *comparison(const char *BYTE, const char NUMB, const char BIG_LETTERS, const char MINI_LETTERS, const char
// SYMB)
// {
//     if (IDENTICAL == 0)
//     {
//     }
//     if (IDENTICAL == 1)
//     {
//         const char *mask[] = {"21", "23", "24", "25", "26", "32", "33", "34", "35", "36", "37", "38", "39",
//                               "40", "41", "42", "43", "44", "45", "46", "47", "48", "4a", "4b", "4c", "4d",
//                               "4e", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "5a", "5e",
//                               "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b", "6d", "6e",
//                               "6f", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "7a"};
//         int mask_sz = sizeof(mask) / sizeof(*mask);

//         for (int num_of_mask_element = 0; num_of_mask_element < mask_sz; num_of_mask_element++)
//             if (strcmp(BYTE, mask[num_of_mask_element]) == 0)
//                 return BYTE;
//         return NULL;
//     }
//     return 0;
// }
