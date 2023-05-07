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
    memcpy(x, input, 16);

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

        memcpy(x, y, 16);
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
// Generate random data using the Fortuna algorithm
void fortuna_generate(fortuna_state_t *state, unsigned char *output, int output_len) {
    int i;
    unsigned char hash_input[BLOCK_SIZE];
    unsigned char hash_output[BLOCK_SIZE];
    unsigned char key_stream[BLOCK_SIZE];
    int bytes_generated = 0;

    // Generate the key stream
    salsa20_20(key_stream, state->counter);

    // Increment the counter
    state->counter[0]++;

    // Compute the hash of the key stream and pool data
    memcpy(hash_input, key_stream, BLOCK_SIZE);
    memcpy(&hash_input[BLOCK_SIZE], state->pool, state->pool_len);
    sha256(hash_output, hash_input, BLOCK_SIZE + state->pool_len);

    // Copy the first 16 bytes of the hash to the output buffer
    for (i = 0; i < 16 && bytes_generated < output_len; i += 4) {
        unsigned int rand_uint = bytes_to_uint(&hash_output[i]);
        memcpy(&output[bytes_generated], &rand_uint, sizeof(unsigned int));
        bytes_generated += sizeof(unsigned int);
    }

    // If necessary, reseed the PRNG
    state->reseed_count++;

    if (state->reseed_count >= 10000) {
        fortuna_reseed(state);
    }
}


// Convert a byte array into an unsigned integer
static unsigned int bytes_to_uint(const unsigned char *bytes) {
    unsigned int result = 0;
    int i;

    for (i = 0; i < 4; i++) {
        result |= (unsigned int)bytes[i] << (8 * i);
    }

    return result;
}


// Test the Fortuna PRNG by generating 16 bytes of random data
int main()
{
    fortuna_state_t state;
    fortuna_init(&state);

    unsigned char output[16];
    fortuna_generate(&state, output, 16);
    bytes_to_ints();    

    int i;
    printf("Random bytes:");
    for (i = 0; i < 16; i++)
    {
        printf(" %02x", output[i]);
    }
    printf("\n");

    return 0;
}