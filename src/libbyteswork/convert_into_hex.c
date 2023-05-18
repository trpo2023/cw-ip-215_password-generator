#include "convert_into_hex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *convert_into_hex(char **BYTE, int SZ)
{
    char *hex_codes = (char *)malloc(sizeof(char) * (SZ * 4)); // выделение памяти для массива с 16-ричными значениями

    for (int i = 0; i < SZ; i++)
    {
        char hex[4] = "0x";

        if (strlen(BYTE[i]) == 1)
        { // обработка регистра размером "1"
            hex[2] = BYTE[i][0];
        }
        else
        {
            hex[2] = BYTE[i][0]; // копирование первого символа
            hex[3] = BYTE[i][1]; // копирование второго символа
        }

        strcat(hex_codes, hex); // добавление 16-ричного значения в массив
        // strcat(hex_codes, " "); // добавление пробела

        printf("%s", hex_codes);
    }
    return hex_codes;
}
#include "convert_into_hex.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char arr[][3] = {"82", "bc", "97", "98", "31", "e0", "b8", "3c", "4f", "33", "d0", "8d", "52", "5f", "46", "c4"};
    int size = sizeof(arr) / sizeof(arr[0]); // получить размер массива

    char **dynamic_arr = (char **)malloc(sizeof(char *) * size); // выделение памяти для динамического массива
    for (int i = 0; i < size; i++)
    {
        dynamic_arr[i] = (char *)malloc(sizeof(char) * 3);
        strcpy(dynamic_arr[i], arr[i]); // копирование значений в динамический массив
    }

    char *hex_array = convert_into_hex(dynamic_arr, size); // вызов функции convert_into_hex

    printf("%s", hex_array); // вывод 16-ричных значений

    // освобождение памяти
    for (int i = 0; i < size; i++)
    {
        free(dynamic_arr[i]);
    }
    free(dynamic_arr);
    free(hex_array);

    return 0;
}
