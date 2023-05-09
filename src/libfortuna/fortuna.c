#include "memcpy_s.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_POOL_SIZE 64
#define MAX_KEY_SIZE 32
#define BLOCK_SIZE 16

// Define the structure for the PRNG state
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

// Define the Salsa20/20 function
static void salsa20_20(unsigned char *output, const unsigned char *input)
{
    int i;
    unsigned char x[16], y[16];
    memcpy_s(x, 16, input, 16);

    for (i = 0; i < 10; i++)
    {
        y[0] = x[0] ^ x[4] ^ x[8] ^ 0x9e;
        y[1] = x[1] ^ x[5] ^ x[9] ^ 0xa4;
        y[2] = x[2] ^ x[6] ^ x[10] ^ 0x6f;
        y[3] = x[3] ^ x[7] ^ x[11] ^ 0xf5;
        y[4] = x[4] ^ x[8] ^ x[12] ^ 0x5d;
        y[5] = x[5] ^ x[9] ^ x[13] ^ 0x10;
        y[6] = x[6] ^ x[10] ^ x[14] ^ 0x26;
        y[7] = x[7] ^ x[11] ^ x[15] ^ 0x19;
        y[8] = x[8] ^ x[12] ^ x[0] ^ 0x9e;
        y[9] = x[9] ^ x[13] ^ x[1] ^ 0xa4;
        y[10] = x[10] ^ x[14] ^ x[2] ^ 0x6f;
        y[11] = x[11] ^ x[15] ^ x[3] ^ 0xf5;
        y[12] = x[12] ^ x[0] ^ x[4] ^ 0x5d;
        y[13] = x[13] ^ x[1] ^ x[5] ^ 0x10;
        y[14] = x[14] ^ x[2] ^ x[6] ^ 0x26;
        y[15] = x[15] ^ x[3] ^ x[7] ^ 0x19;

        memcpy_s(x, 16, input, 16);
    }

    for (i = 0; i < 16; i++)
    {
        output[i] = x[i] + input[i];
    }
}

// Initialize the PRNG state
void fortuna_init(fortuna_state_t *state)
{
    // Set the key and counter to all zeros
    memset(state->key, 0, MAX_KEY_SIZE);
    memset(state->counter, 0, BLOCK_SIZE);

    // Initialize the pool with random data
    srand(time(NULL)); // Seed the random number generator with the current time
    int i;
    for (i = 0; i < MAX_POOL_SIZE; i++)
    {
        state->pool[i] = rand() % 256; // Generate a random byte
    }
    state->pool_len = MAX_POOL_SIZE;
    state->pool_index = 0;
    state->reseed_count = 0;
}

// Reseed the PRNG with new entropy data
void fortuna_reseed(fortuna_state_t *state, const unsigned char *entropy, int entropy_len)
{
    // Update the counter and cipher with the new entropy data
    int i;
    for (i = 0; i < BLOCK_SIZE; i++)
    {
        state->counter[i] += entropy[i];
    }
    salsa20_20(state->cipher, state->counter);
    // XOR the new entropy data with the pool
    for (i = 0; i < entropy_len; i++)
    {
        state->pool[state->pool_index] ^= entropy[i];
        state->pool_index = (state->pool_index + 1) % MAX_POOL_SIZE;
    }

    // Increment the reseed count
    state->reseed_count++;
}

// Generate a random block of data
void fortuna_generate(fortuna_state_t *state, unsigned char *output, int output_len)
{
    // Reseed if necessary
    if (state->reseed_count >= 10000)
    {
        fortuna_reseed(state, state->pool, state->pool_len);
    }
    // Generate the requested output
    int i, j;
    unsigned char buffer[BLOCK_SIZE];
    for (i = 0; i < output_len; i += BLOCK_SIZE)
    {
        // Increment the counter and generate a new cipher with Salsa20/20
        for (j = 0; j < BLOCK_SIZE; j++)
        {
            state->counter[j]++;
            if (state->counter[j] != 0)
                break;
        }
        salsa20_20(buffer, state->counter);

        // XOR the cipher with the pool and output the result
        for (j = 0; j < BLOCK_SIZE; j++)
        {
            output[i + j] = buffer[j] ^ state->pool[state->pool_index];
            state->pool[state->pool_index] = buffer[j];
            state->pool_index = (state->pool_index + 1) % MAX_POOL_SIZE;
        }
    }
}

// Test the Fortuna PRNG by generating 16 bytes of random data
int main()
{
    fortuna_state_t state;
    fortuna_init(&state);
    unsigned char output[16];
    fortuna_generate(&state, output, 16);

    int i;
    for (i = 0; i < 16; i++)
    {
        printf(" %x", output[i]);
    }
    printf("\n");
}