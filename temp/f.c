#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROTL(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) (			\
	a += b,  d ^= a,  d = ROTL(d,16),	\
	c += d,  b ^= c,  b = ROTL(b,12),	\
	a += b,  d ^= a,  d = ROTL(d, 8),	\
	c += d,  b ^= c,  b = ROTL(b, 7))

typedef struct
{
    unsigned char pool[64];
    int pool_index;
    int update_count;
    unsigned char counter[16];
    unsigned char cipher[16];
} generator_str;

static void chacha20_20(const unsigned char *input, unsigned char *output)
{
    int i;
    int x[16];

    for (i = 0; i < 16; ++i)
        x[i] = input[i];
    for (i = 0; i < 20; i += 2)
    {
        QR(x[0], x[4], x[8], x[12]);
        QR(x[1], x[5], x[9], x[13]);
        QR(x[2], x[6], x[10], x[14]);
        QR(x[3], x[7], x[11], x[15]);
        QR(x[0], x[5], x[10], x[15]);
        QR(x[1], x[6], x[11], x[12]);
        QR(x[2], x[7], x[8], x[13]);
        QR(x[3], x[4], x[9], x[14]);
    }
    for (i = 0; i < 16; ++i)
        output[i] = x[i] + input[i];
}

void fortuna_initialize(generator_str *state)
{
    memset(state->counter, 0, 16);

    // инициализация пула с рандомными числами
    for (int i = 0; i < 64; i++)
        state->pool[i] = rand() % 256;
    state->pool_index = 0;
    state->update_count = 0;
}

// Reseed the PRNG with new entropy data
void fortuna_update(generator_str *state, const unsigned char *entropy, int entropy_len)
{
    // Update the counter and cipher with the new entropy data
    for (int i = 0; i < 16; i++)
    {
        state->counter[i] += entropy[i];
    }
    chacha20_20(state->counter, state->cipher);
    // XOR the new entropy data with the pool
    for (int i = 0; i < entropy_len; i++)
    {
        state->pool[state->pool_index] ^= entropy[i];
        state->pool_index = (state->pool_index + 1) % 64;
    }

    // Increment the reseed count
    state->update_count++;
}

// Generate a random block of data
void fortuna_generate_byte(generator_str *state, unsigned char *output)
{
    // Reseed if necessary
    if (state->update_count >= 10000)
    {
        fortuna_update(state, state->pool, 64);
    }
    // Generate the requested output
    unsigned char buffer[16];
    for (int i = 0; i < 1; i += 16)
    {
        // Increment the counter and generate a new cipher with Salsa20/20
        for (int j = 0; j < 16; j++)
        {
            state->counter[j]++;
            if (state->counter[j] != 0)
                break;
        }
        chacha20_20(state->counter, buffer);

        // XOR the cipher with the pool and output the result
        for (int j = 0; j < 16; j++)
        {
            output[i + j] = buffer[j] ^ state->pool[state->pool_index];
            state->pool[state->pool_index] = buffer[j];
            state->pool_index = (state->pool_index + 1) % 64;
        }
    }
}

// Test the Fortuna PRNG by generating 16 bytes of random data
int main()
{
    generator_str state;

    fortuna_initialize(&state);
    unsigned char chacha_out[16];

    fortuna_generate_byte(&state, chacha_out);

    printf("%02x", chacha_out[0]);

    return 0;
}