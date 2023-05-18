#include "memset_s.h"
#include "rdrand.h"
#include "chacha20.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POOL_SIZE 64
#define MAX_KEY_SIZE 32
#define BLOCK_SIZE 16

int GENERATE_SIZE = 16;

typedef struct
{
    unsigned char key[MAX_KEY_SIZE];
    unsigned char pool[MAX_POOL_SIZE];
    int pool_len;
    int pool_index;
    unsigned char counter[BLOCK_SIZE];
    unsigned char cipher[BLOCK_SIZE];
    int reseed_count;
} fortuna_state_t;

/*
 * Инициализация PRNG: Устанавливает ключ и счетчик на 0, инициализирует пул случайными данными и устанавливает
 * количество регенераций (reseed count) в ноль.
 */
static void fortuna_init(fortuna_state_t *state)
{
    // Установка ключа и счетчика на 0
    memset(state->key, 0, MAX_KEY_SIZE);
    memset(state->counter, 0, BLOCK_SIZE);

    // Инициализация пула со случайными данными
    int i;
    for (i = 0; i < MAX_POOL_SIZE; i++)
    {
        state->pool[i] = rdrand() % 256; // Генерация случайного байта
    }
    state->pool_len = MAX_POOL_SIZE;
    state->pool_index = 0;
    state->reseed_count = 0;
}

/*
 * Обновить состояние PRNG с помощью новых энтропийных данных (обновляет счетчик и шифр, используя новые данные
 * энтропии, а затем XOR-ит новые данные энтропии с пулом)
 */
static void fortuna_reseed(fortuna_state_t *state, const unsigned char *entropy, int entropy_len)
{
    // Обновление счётчика и шифра новой энтропией
    int i;
    for (i = 0; i < BLOCK_SIZE; i++)
    {
        state->counter[i] += entropy[i];
    }
    chacha20_20(state->cipher, state->counter);

    // XOR-им новые данные энтропии с пулом
    for (i = 0; i < entropy_len; i++)
    {
        state->pool[state->pool_index] ^= entropy[i];
        state->pool_index = (state->pool_index + 1) % MAX_POOL_SIZE;
    }

    // Увеличение счетчика reseed
    state->reseed_count++;
}

/*
 * Генерация блока случайных чисел (если количество регенераций превышает 10 000, функция вызывает
 * fortuna_reseed для обновления состояния PRNG, затем использует ChaCha20/20 для генерации нового блока данных,
 * выполняя XOR с пулом и выводя результат в выходной массив)
 */
static void fortuna_generate(fortuna_state_t *state, unsigned char *output, int output_len)
{
    // Reseed, если необходимо
    if (state->reseed_count >= 10000)
    {
        fortuna_reseed(state, state->pool, state->pool_len);
    }
    // Генерация запрашиваемого вывода
    int i, j;
    unsigned char buffer[BLOCK_SIZE];
    for (i = 0; i < output_len; i += BLOCK_SIZE)
    {
        // Increment the counter and generate a new cipher with ChaCha20/20
        for (j = 0; j < BLOCK_SIZE; j++)
        {
            state->counter[j]++;
            if (state->counter[j] != 0)
                break;
        }
        chacha20_20(buffer, state->counter);

        // XOR the cipher with the pool and output the result
        for (j = 0; j < BLOCK_SIZE; j++)
        {
            output[i + j] = buffer[j] ^ state->pool[state->pool_index];
            state->pool[state->pool_index] = buffer[j];
            state->pool_index = (state->pool_index + 1) % MAX_POOL_SIZE;
        }
    }
}

/*
 * Генерация числа с помощью всех функций программы
 */
int fortuna()
{
    fortuna_state_t state;
    fortuna_init(&state);
    unsigned char output[GENERATE_SIZE];
    fortuna_generate(&state, output, GENERATE_SIZE);

    int i;
    for (i = 0; i < GENERATE_SIZE; i++)
    {
        // printf(" %x", output[i]);
        return output[i];
    }
}