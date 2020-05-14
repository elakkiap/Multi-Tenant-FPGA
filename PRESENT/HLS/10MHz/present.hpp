#ifndef PRESENT_H
#define PRESENT_H
#include "stdint.h"
#define ROUNDS 32 // Number of rounds the present algorithm runs in order to generate the cipher
#define SBOX_SIZE 16
#define PBOX_SIZE 64

typedef uint64_t block_size;
typedef uint16_t key_size;

void present_encrypt(key_size key_high, block_size key_low, block_size block,
		block_size *cipher);

#endif
