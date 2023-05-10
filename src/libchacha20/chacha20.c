#include "chacha20.h"

#define ROTL(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) (			\
	a += b,  d ^= a,  d = ROTL(d,16),	\
	c += d,  b ^= c,  b = ROTL(b,12),	\
	a += b,  d ^= a,  d = ROTL(d, 8),	\
	c += d,  b ^= c,  b = ROTL(b, 7))

/*
 * Поточный шифр Salsa20 с 20 циклами
 */

void chacha20_20(unsigned char *output, const unsigned char *input)
{
    int i;
    unsigned char x[16];

    for (i = 0; i < 16; ++i)
        x[i] = input[i];

    for (i = 0; i < 20; i += 2)
    {
        // Нечетный раунд
        QR(x[0], x[4], x[ 8], x[12]);
		QR(x[1], x[5], x[ 9], x[13]);
		QR(x[2], x[6], x[10], x[14]);
		QR(x[3], x[7], x[11], x[15]);
        // Четный раунд
        QR(x[0], x[5], x[10], x[15]);
		QR(x[1], x[6], x[11], x[12]);
		QR(x[2], x[7], x[ 8], x[13]);
		QR(x[3], x[4], x[ 9], x[14]);
    }
    for (i = 0; i < 16; i++)
        output[i] = x[i] + input[i];
}