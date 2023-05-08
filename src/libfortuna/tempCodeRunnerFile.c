void fortuna_generate(fortuna_state_t *state, unsigned char *output, int len)
{
    int i, j;
    unsigned char data[BLOCK_SIZE];

    // Generate the required amount of random data
    for (i = 0; i < len; i++)
    {
        // Check if the pool needs to be reseeded
        if (state->reseed_count >= 10000)
        {
            fortuna_reseed(state, entropy, entropy_len);
        }

        // Generate a block of random data using Salsa20/20
        salsa20_20(data, state->counter);
        for (j = 0; j < BLOCK_SIZE; j++)
        {
            state->counter[j]++;
        }

        // XOR the random data with the pool and output it
        output[i] = data[0] ^ state->pool[state->pool_index];
        state->pool[state->pool_index] = output[i];
        state->pool_index = (state->pool_index + 1) % state->pool_len;

        // Update the reseed counter
        state->reseed_count++;
    }

    // Convert the random data to characters
    for (i = 0; i < len; i++)
    {
        output[i] = output[i] % 26 + 'A'; // Convert to uppercase letters
    }
}