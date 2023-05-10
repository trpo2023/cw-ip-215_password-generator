#include "convert_to_utf_8.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char input[] = {"0x82", "0xbc", "0x97", "0x98", "0x31", "0xe0", "0xb8", "0x3c",
                    "0x4f", "0x33", "0xd0", "0x8d", "0x52", "0x5f", "0x46", "0xc4"}; // example input array
    int input_length = sizeof(input) / sizeof(input[0]);
    char output[5]; // output string buffer

    for (int i = 0; i < input_length; i++)
    {
        // convert hex string to integer value
        int value = strtol(input[i], NULL, 16);

        // convert integer value to UTF-8 character
        if (value <= 0x7F)
        {
            output[i] = value;
        }
        else if (value <= 0x7FF)
        {
            output[i] = ((value >> 6) & 0x1F) | 0xC0;
            output[++i] = (value & 0x3F) | 0x80;
        }
        else if (value <= 0xFFFF)
        {
            output[i] = ((value >> 12) & 0x0F) | 0xE0;
            output[++i] = ((value >> 6) & 0x3F) | 0x80;
            output[++i] = (value & 0x3F) | 0x80;
        }
        else
        {
            output[i] = ((value >> 18) & 0x07) | 0xF0;
            output[++i] = ((value >> 12) & 0x3F) | 0x80;
            output[++i] = ((value >> 6) & 0x3F) | 0x80;
            output[++i] = (value & 0x3F) | 0x80;
        }
    }

    // print output string
    printf("Output string: %s\n", output);

    return 0;
}
