#include <stdlib.h>
#include <string.h>

char* convert_into_hex(char** arr, int size)
{
    char* hex_array = (char*)malloc(sizeof(char) * (size * 4)); // выделение памяти для массива с 16-ричными значениями

    for (int i = 0; i < size; i++)
    {
        char hex[4] = "0x"; // инициализация 16-ричного префикса

        if (strlen(arr[i]) == 1)
        { // обработка регистра размером "1"
            hex[2] = arr[i][0];
        }
        else
        {
            hex[2] = arr[i][0]; // копирование первого символа
            hex[3] = arr[i][1]; // копирование второго символа
        }

        strcat(hex_array, hex); // добавление 16-ричного значения в массив
        strcat(hex_array, " "); // добавление пробела
    }

    return hex_array;
}
