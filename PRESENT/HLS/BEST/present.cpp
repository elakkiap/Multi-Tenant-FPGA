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

block_size addRoundKey(block_size current_state, block_size key) {
	return current_state ^ key;
}

block_size sBoxLayer(block_size current_state) {
#pragma HLS ARRAY_PARTITION variable=s_box complete dim=1
	block_size output = 0;
	for (int i = 0; i < SBOX_SIZE; i++) {
#pragma HLS UNROLL
		output = output | (s_box[(current_state >> (i * 4)) & 0xF] << (i * 4));
	}
	return output;
}

block_size PLayer(block_size current_state) {
#pragma HLS ARRAY_PARTITION variable=p_box complete dim=1
	block_size output = 0;
	for (block_size i = 0; i < PBOX_SIZE; i++) {
#pragma HLS UNROLL
		output = output | (((current_state >> i) & 0x01) << p_box[i]);
	}
	return output;
}

void present_1(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}

void present_2(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}

void present_3(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_4(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_5(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}

void present_6(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}

void present_7(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_8(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}

void present_9(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}

void present_10(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}

void present_11(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_12(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_13(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}

void present_14(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}

void present_15(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_16(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_17(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_18(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_19(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_20(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_21(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_22(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_23(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_24(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_25(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}

void present_26(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_27(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_28(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}

void present_29(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_30(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_31(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, key_size *key_highout, block_size *key_lowout,
		block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	key_low_t = key_low;
	key_high = ((key_low_t << 45) & 0xffff000000000000) >> 48;
	key_low = ((key_low_t << 61) & 0xe000000000000000) | (key_temp << 45)
			| (key_low_t >> 19);
	*key_highout = (s_box[(key_high >> 12) & 0Xf] << 12)
			| (((key_high << 4) >> 4) & 0x0fff);
	*key_lowout = key_low ^ (round_number << 15);
	temp_block = addRoundKey(block_in, roundkey);
	temp_block = sBoxLayer(temp_block);
	temp_block = PLayer(temp_block);
	*block_out = temp_block;
}
void present_32(key_size key_high, block_size key_low, block_size block_in,
		block_size round_number, block_size *block_out) {
	block_size i, l_i;
	block_size key_low_t, key_temp, roundkey, temp_block;
	key_temp = key_high;
	roundkey = (key_temp << 48) | ((key_low >> 16) & 0x0000ffffffffffff);
	temp_block = addRoundKey(block_in, roundkey);
	*block_out = temp_block;

}
void present_encrypt(key_size key_high, block_size key_low,
		block_size plain_text, block_size *cipher) {
	block_size block2, key_low2, block3, key_low3, block4, key_low4, block5,
			key_low5, block6, key_low6, block7, key_low7, block8, key_low8,
			block9, key_low9, block10, key_low10, block11, key_low11, block12,
			key_low12, block13, key_low13, block14, key_low14, block15,
			key_low15, block16, key_low16, block17, key_low17, block18,
			key_low18, block19, key_low19, block20, key_low20, block21,
			key_low21, block22, key_low22, block23, key_low23, block24,
			key_low24, block25, key_low25, block26, key_low26, block27,
			key_low27, block28, key_low28, block29, key_low29, block30,
			key_low30, block31, key_low31, block32, key_low32, final_block;
	key_size high_key2, high_key3, high_key4, high_key5, high_key6, high_key7,
			high_key8, high_key9, high_key10, high_key11, high_key12,
			high_key13, high_key14, high_key15, high_key16, high_key17,
			high_key18, high_key19, high_key20, high_key21, high_key22,
			high_key23, high_key24, high_key25, high_key26, high_key27,
			high_key28, high_key29, high_key30, high_key31, high_key32;
#pragma HLS DATAFLOW
	present_1(key_high, key_low, plain_text, 1, &high_key2, &key_low2, &block2);
	present_2(high_key2, key_low2, block2, 2, &high_key3, &key_low3, &block3);
	present_3(high_key3, key_low3, block3, 3, &high_key4, &key_low4, &block4);
	present_4(high_key4, key_low4, block4, 4, &high_key5, &key_low5, &block5);
	present_5(high_key5, key_low5, block5, 5, &high_key6, &key_low6, &block6);
	present_6(high_key6, key_low6, block6, 6, &high_key7, &key_low7, &block7);
	present_7(high_key7, key_low7, block7, 7, &high_key8, &key_low8, &block8);
	present_8(high_key8, key_low8, block8, 8, &high_key9, &key_low9, &block9);
	present_9(high_key9, key_low9, block9, 9, &high_key10, &key_low10,
			&block10);
	present_10(high_key10, key_low10, block10, 10, &high_key11, &key_low11,
			&block11);
	present_11(high_key11, key_low11, block11, 11, &high_key12, &key_low12,
			&block12);
	present_12(high_key12, key_low12, block12, 12, &high_key13, &key_low13,
			&block13);
	present_13(high_key13, key_low13, block13, 13, &high_key14, &key_low14,
			&block14);
	present_14(high_key14, key_low14, block14, 14, &high_key15, &key_low15,
			&block15);
	present_15(high_key15, key_low15, block15, 15, &high_key16, &key_low16,
			&block16);
	present_16(high_key16, key_low16, block16, 16, &high_key17, &key_low17,
			&block17);
	present_17(high_key17, key_low17, block17, 17, &high_key18, &key_low18,
			&block18);
	present_18(high_key18, key_low18, block18, 18, &high_key19, &key_low19,
			&block19);
	present_19(high_key19, key_low19, block19, 19, &high_key20, &key_low20,
			&block20);
	present_20(high_key20, key_low20, block20, 20, &high_key21, &key_low21,
			&block21);
	present_21(high_key21, key_low21, block21, 21, &high_key22, &key_low22,
			&block22);
	present_22(high_key22, key_low22, block22, 22, &high_key23, &key_low23,
			&block23);
	present_23(high_key23, key_low23, block23, 23, &high_key24, &key_low24,
			&block24);
	present_24(high_key24, key_low24, block24, 24, &high_key25, &key_low25,
			&block25);
	present_25(high_key25, key_low25, block25, 25, &high_key26, &key_low26,
			&block26);
	present_26(high_key26, key_low26, block26, 26, &high_key27, &key_low27,
			&block27);
	present_27(high_key27, key_low27, block27, 27, &high_key28, &key_low28,
			&block28);
	present_28(high_key28, key_low28, block28, 28, &high_key29, &key_low29,
			&block29);
	present_29(high_key29, key_low29, block29, 29, &high_key30, &key_low30,
			&block30);
	present_30(high_key30, key_low30, block30, 30, &high_key31, &key_low31,
			&block31);
	present_31(high_key31, key_low31, block31, 31, &high_key32, &key_low32,
			&block32);
	present_32(high_key32, key_low32, block32, 32, &final_block);
	*cipher = final_block;

}
