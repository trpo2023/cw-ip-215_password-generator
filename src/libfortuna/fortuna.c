#include "fortuna.h"

#include "chacha20.h"
#include "memset_s.h"
#include "rdrand.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 64
#define KEY_SIZE 32
#define BLOCK_SIZE 16

int GENERATE_SIZE = 1;

typedef struct
{
    unsigned char key[KEY_SIZE];
    unsigned char pool[POOL_SIZE];
    int pool_length;
    int pool_index;
    unsigned char counter[BLOCK_SIZE];
    unsigned char cypher[BLOCK_SIZE];
    int count_of_new_seed;
} fortuna_struct;

/*
 * Инициализация PRNG: Устанавливает ключ и счетчик на 0, инициализирует пул случайными данными и устанавливает
 * количество регенераций (reseed count) в ноль.
 */
static void fortuna_init(fortuna_struct *state)
{
    // Установка ключа и счетчика на 0
    memset(state->key, 0, KEY_SIZE);
    memset(state->counter, 0, BLOCK_SIZE);

    // Инициализация пула со случайными данными
    int i;
    for (i = 0; i < POOL_SIZE; i++)
    {
        state->pool[i] = rdrand() % 256; // Генерация случайного байта
    }
    state->pool_length = POOL_SIZE;
    state->pool_index = 0;
    state->count_of_new_seed = 0;
}

/*
 * Обновить состояние PRNG с помощью новых энтропийных данных (обновляет счетчик и шифр, используя новые данные
 * энтропии, а затем XOR-ит новые данные энтропии с пулом)
 */
static void fortuna_reseed(fortuna_struct *state, const unsigned char *entropy, int entropy_len)
{
    // Обновление счётчика и шифра новой энтропией
    int i;
    for (i = 0; i < BLOCK_SIZE; i++)
    {
        state->counter[i] += entropy[i];
    }
    chacha20_20(state->cypher, state->counter);

    // XOR-им новые данные энтропии с пулом
    for (i = 0; i < entropy_len; i++)
    {
        state->pool[state->pool_index] ^= entropy[i];
        state->pool_index = (state->pool_index + 1) % POOL_SIZE;
    }

    // Увеличение счетчика reseed
    state->count_of_new_seed++;
}

/*
 * Генерация блока случайных чисел (если количество регенераций превышает 10 000, функция вызывает
 * fortuna_reseed для обновления состояния PRNG, затем использует ChaCha20/20 для генерации нового блока данных,
 * выполняя XOR с пулом и выводя результат в выходной массив)
 */
static void fortuna_generate(fortuna_struct *state, unsigned char *output, int output_len)
{
    // Reseed, если необходимо
    if (state->count_of_new_seed >= 10000)
    {
        fortuna_reseed(state, state->pool, state->pool_length);
    }
    // Генерация запрашиваемого вывода
    int i, j;
    unsigned char buffer[BLOCK_SIZE];
    for (i = 0; i < output_len; i += BLOCK_SIZE)
    {
        // Increment the counter and generate a new cypher with ChaCha20/20
        for (j = 0; j < BLOCK_SIZE; j++)
        {
            state->counter[j]++;
            if (state->counter[j] != 0)
                break;
        }
        chacha20_20(buffer, state->counter);

        // XOR the cypher with the pool and output the result
        for (j = 0; j < BLOCK_SIZE; j++)
        {
            output[i + j] = buffer[j] ^ state->pool[state->pool_index];
            state->pool[state->pool_index] = buffer[j];
            state->pool_index = (state->pool_index + 1) % POOL_SIZE;
        }
    }
}

/*
 * Генерация числа с помощью всех функций программы
 */
int fortuna()
{
    fortuna_struct state;
    fortuna_init(&state);
    unsigned char output[GENERATE_SIZE];
    
    fortuna_generate(&state, output, GENERATE_SIZE);

    int i;
    if (GENERATE_SIZE == 1)
        return output[0];
    else
        for (i = 0; i < GENERATE_SIZE; i++)
            return output[i];
    return 0;
}