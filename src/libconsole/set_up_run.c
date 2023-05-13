#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("%s\n", argv[0]); // получение имени программы

    for (int i = 1; i < argc; ++i) // получение параметров из команды терминала вида "имя_программы -параметр -параметр"
    {
        printf("%d. %s\n", i, argv[i]);
    }
    return 0;
}
