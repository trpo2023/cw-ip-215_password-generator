#include "memcpy_s.h"
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