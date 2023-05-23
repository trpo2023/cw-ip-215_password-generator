#include <stdio.h>
#include <stdlib.h>

unsigned char *convert_to_UTF8(unsigned int hexNumber)
{
    unsigned char *utf8 = (unsigned char *)malloc(5); // Выделяем память для UTF-8 символа

    if (hexNumber <= 0x7F)
    {
        utf8[0] = hexNumber;
        utf8[1] = '\0';
    }
    else if (hexNumber <= 0x7FF)
    {
        utf8[0] = 0xC0 | ((hexNumber >> 6) & 0x1F);
        utf8[1] = 0x80 | (hexNumber & 0x3F);
        utf8[2] = '\0';
    }
    else if (hexNumber <= 0xFFFF)
    {
        utf8[0] = 0xE0 | ((hexNumber >> 12) & 0x0F);
        utf8[1] = 0x80 | ((hexNumber >> 6) & 0x3F);
        utf8[2] = 0x80 | (hexNumber & 0x3F);
        utf8[3] = '\0';
    }
    else if (hexNumber <= 0x10FFFF)
    {
        utf8[0] = 0xF0 | ((hexNumber >> 18) & 0x07);
        utf8[1] = 0x80 | ((hexNumber >> 12) & 0x3F);
        utf8[2] = 0x80 | ((hexNumber >> 6) & 0x3F);
        utf8[3] = 0x80 | (hexNumber & 0x3F);
        utf8[4] = '\0';
    }
    return utf8;
}