#ifndef PRESENT_H
#define PRESENT_H
#include "ap_int.h"
#define ROUNDS 32 // Number of rounds the present algorithm runs in order to generate the cipher
#define SBOX_SIZE 16
#define PBOX_SIZE 64

typedef ap_uint<64> block_size;
typedef ap_uint<16> key_size;

struct block_t{
	block_size data;
	ap_int<1> last;
};
void present_encrypt(block_t *key_high, block_t *key_low, block_t *block,
		block_t *cipher);

#endif
