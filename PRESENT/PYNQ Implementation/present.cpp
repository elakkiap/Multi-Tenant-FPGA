#include "present.hpp"
#include<stdio.h>
// S-Box Values

block_size s_box[16] = { 0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf,
		0x8, 0x4, 0x7, 0x1, 0x2 };
//P-Box Values
block_size p_box[64] = { 0, 16, 32, 48, 1, 17, 33, 49, 2, 18, 34, 50, 3, 19, 35,
		51, 4, 20, 36, 52, 5, 21, 37, 53, 6, 22, 38, 54, 7, 23, 39, 55, 8, 24,
		40, 56, 9, 25, 41, 57, 10, 26, 42, 58, 11, 27, 43, 59, 12, 28, 44, 60,
		13, 29, 45, 61, 14, 30, 46, 62, 15, 31, 47, 63 };

block_size roundKeys[32];
void generateRoundKeys80(key_size key_high, block_size key_low) {
	block_size i, l_i;
	block_size key_low_t, key_temp;
	for (i = 0; i < ROUNDS; i++) {
		key_temp = key_high;
		roundKeys[i] = (key_temp << 48)
				| ((key_low >> 16) & 0x0000ffffffffffff);
		key_low_t = key_low;
		// Shift by 61 bits
		key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
		key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
				| (key_low_t >> 19);
		// S Box Operations
		key_high = (s_box[(key_high >> 12) & 0Xf] << 12)
				| (((key_high << 4) >> 4) & 0x0fff);
		// XOR with the round_counter
		l_i = ((i + 1) << 15);
		key_low = key_low ^ l_i;

	}
}

block_size addRoundKey(block_size current_state, block_size key) {
	return current_state ^ key;
}

block_size sBoxLayer(block_size current_state) {
	block_size output = 0;
	for (int i = 0; i < SBOX_SIZE; i++) {
		output = output | (s_box[(current_state >> (i * 4)) & 0xF] << (i * 4));
	}
	return output;
}

block_size PLayer(block_size current_state) {
	block_size output = 0;
	for (block_size i = 0; i < PBOX_SIZE; i++) {
		output = output | (((current_state >> i) & 0x01) << p_box[i]);
	}
	return output;
}

void present_encrypt(block_t *key_high, block_t *key_low, block_t *block,
		block_t *cipher) {
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE axis register both depth=1 port=cipher
#pragma HLS INTERFACE axis register both depth=1 port=block
#pragma HLS INTERFACE axis register both depth=1 port=key_low
#pragma HLS INTERFACE axis register both depth=1 port=key_high
	block_t t_cipher, t_high, t_low, t_plain;
	block_size plain;
	t_high = *key_high;
	t_low = *key_low;
	t_plain = *block;
	plain = t_plain.data;
	generateRoundKeys80(t_high.data, t_low.data);
	for (int i = 0; i < ROUNDS - 1; i++) {
#pragma HLS PIPELINE
		plain = addRoundKey(plain, roundKeys[i]);
		plain = sBoxLayer(plain);
		plain = PLayer(plain);
	}
	plain = addRoundKey(plain, roundKeys[ROUNDS - 1]);
	t_cipher.data = plain;
	t_cipher.last = 1;
	*cipher = t_cipher;

}
