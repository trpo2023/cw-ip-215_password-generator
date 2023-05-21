#include "fortuna.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rdrand.h"
#include "chacha20.h"

#define ROTL(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) (			\
	a += b,  d ^= a,  d = ROTL(d,16),	\
	c += d,  b ^= c,  b = ROTL(b,12),	\
	a += b,  d ^= a,  d = ROTL(d, 8),	\
	c += d,  b ^= c,  b = ROTL(b, 7))

typedef struct
{
    unsigned char pool[64];
    int pool_item_number;
    int update_counter;
    unsigned char counter[16];
    unsigned char cypher[16];
} generator_str;

void fortuna_initialize(generator_str *state)
{
    memset(state->counter, 0, sizeof(state->counter));

    for (int i = 0; i < 64; i++)
        state->pool[i] = rdrand() % 256;
    state->pool_item_number = 0;
    state->update_counter = 0;
}

void fortuna_update(generator_str *state, const unsigned char *entropy)
{
    // Обновление счетчика и шифра новой энтропией
    for (int i = 0; i < 16; i++)
        state->counter[i] += entropy[i];
    chacha20_20(state->counter, state->cypher);
    // используем исключающее ИЛИ
    for (int i = 0; i < 64; i++)
    {
        state->pool[state->pool_item_number] ^= entropy[i];
        state->pool_item_number = (state->pool_item_number + 1) % 64;
    }
    state->update_counter++;
}

void fortuna_generate_byte(generator_str *state, unsigned char *array)
{
    if (state->update_counter >= 10000)
        fortuna_update(state, state->pool);

    // Генерация бита
    unsigned char temp[16];
    for (int i = 0; i < 1; i += 16)
    {
        // Increment the counter and generate a new cypher with Salsa20/20
        for (int j = 0; j < 16; j++)
        {
            state->counter[j]++;
            if (state->counter[j] != 0)
                break;
        }
        chacha20_20(state->counter, temp);

        // побитовое ИЛИ для шифра, используя пул 
        for (int j = 0; j < 16; j++)
        {
            array[i + j] = temp[j] ^ state->pool[state->pool_item_number];
            state->pool[state->pool_item_number] = temp[j];
            state->pool_item_number = (state->pool_item_number + 1) % 64;
        }
    }
}

char fortuna()
{
    generator_str state;

    fortuna_initialize(&state);
    unsigned char chacha_out[16];

    fortuna_generate_byte(&state, chacha_out);

    return chacha_out[0];
}