/*
 * Генерация числа с помощью всех функций программы
 */
int main()
{
    fortuna_state_t state;
    fortuna_init(&state);
    unsigned char output[GENERATE_SIZE];
    fortuna_generate(&state, output, GENERATE_SIZE);

    int i;
    for (i = 0; i < GENERATE_SIZE; i++)
    {
        printf(" %x", output[i]);
    }
    printf("\n");
}