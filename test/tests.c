#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ctest.h"
#include "rdrand.h"

CTEST(generation, randomness_of_RDRAND)
{
    int RD_KEY = 32;

    int arr[RD_KEY];

    double result = 0;
    int error_count = 0;

    for (int i = 0; i < RD_KEY; i++)
    {
        arr[i] = abs(rdrand() % 2);

        if (arr[i] == 1)
            result += 1;
        else
            result -= 1;
    }

    result = fabs(result) / sqrt(RD_KEY);
    result = erfc(result);

    if (result < 0.01)
        error_count++;

    ASSERT_EQUAL(0, error_count);
}

#include "fortuna.h"

CTEST(generation, working_capacity_of_Fortuna)
{
    unsigned char fortuna_output = 0;
    fortuna_output = fortuna();

    ASSERT_TRUE(fortuna_output);
}

#include "chacha20.h"

CTEST(generation, result_of_chacha20)
{
    unsigned char input[] = {0x07, 0x1B, 0x2C, 0x3D, 0x4E, 0x5F, 0x60, 0x71,
                             0x82, 0x93, 0xA4, 0xB5, 0xC6, 0xD7, 0xE8, 0xF9};
    unsigned char output[16];

    chacha20_20(input, output);

    unsigned char expected[] = {0xdc, 0x95, 0x38, 0xeb, 0xce, 0x5f, 0xe0, 0x71,
                                0x04, 0x26, 0x48, 0x6a, 0xc6, 0xd7, 0xe8, 0xf9};
    ASSERT_DATA(expected, 16, output, 16);
}

#include "comparison.h"

CTEST(mask, wrong_symbol)
{
    unsigned char fortuna_output = 0xAA;

    int numbers = 1;
    int capital_letters = 1;
    int lowercase_letters = 1;
    int symbols = 1;

    comparison(&fortuna_output, numbers, capital_letters, lowercase_letters, symbols);
    ASSERT_TRUE(!fortuna_output);
}

CTEST(mask, wrong_symbol_before_array)
{
    unsigned char fortuna_output = 0x23;

    int numbers = 0;
    int capital_letters = 0;
    int lowercase_letters = 1;
    int symbols = 0;

    comparison(&fortuna_output, numbers, capital_letters, lowercase_letters, symbols);
    ASSERT_TRUE(!fortuna_output);
}

CTEST(mask, wrong_symbol_after_array)
{
    unsigned char fortuna_output = 0x58;

    int numbers = 0;
    int capital_letters = 0;
    int lowercase_letters = 0;
    int symbols = 1;

    comparison(&fortuna_output, numbers, capital_letters, lowercase_letters, symbols);
    ASSERT_TRUE(!fortuna_output);
}

CTEST(mask, right_symbol_symbols)
{
    unsigned char fortuna_output = 0x24;

    int numbers = 0;
    int capital_letters = 0;
    int lowercase_letters = 0;
    int symbols = 1;

    comparison(&fortuna_output, numbers, capital_letters, lowercase_letters, symbols);
    ASSERT_TRUE(fortuna_output);
}

CTEST(mask, right_symbol_lowercase_letters)
{
    unsigned char fortuna_output = 0x71;

    int numbers = 0;
    int capital_letters = 0;
    int lowercase_letters = 1;
    int symbols = 0;

    comparison(&fortuna_output, numbers, capital_letters, lowercase_letters, symbols);
    ASSERT_TRUE(fortuna_output);
}

CTEST(mask, right_symbol_capital_letters)
{
    unsigned char fortuna_output = 0x44;

    int numbers = 0;
    int capital_letters = 1;
    int lowercase_letters = 0;
    int symbols = 0;

    comparison(&fortuna_output, numbers, capital_letters, lowercase_letters, symbols);
    ASSERT_TRUE(fortuna_output);
}

CTEST(mask, right_symbol_numbers)
{
    unsigned char fortuna_output = 0x37;

    int numbers = 1;
    int capital_letters = 0;
    int lowercase_letters = 0;
    int symbols = 0;

    comparison(&fortuna_output, numbers, capital_letters, lowercase_letters, symbols);
    ASSERT_TRUE(fortuna_output);
}

CTEST(mask, right_symbol)
{
    unsigned char fortuna_output = 0x66;

    int numbers = 1;
    int capital_letters = 1;
    int lowercase_letters = 1;
    int symbols = 1;

    comparison(&fortuna_output, numbers, capital_letters, lowercase_letters, symbols);
    ASSERT_TRUE(fortuna_output);
}

#include "convert_to_UTF8.h"

CTEST(convertion, to_UTF8)
{
    unsigned char fortuna_output = 0x5e; // символ "^"

    unsigned char *result = convert_to_UTF8(fortuna_output);

    int expected = 94;
    ASSERT_EQUAL_U(expected, *result);
}

CTEST(app, run)
{
    const char *program_name = "./pwgen_app -ctest";

    int result = system(program_name);
    ASSERT_TRUE(result == 0);
}