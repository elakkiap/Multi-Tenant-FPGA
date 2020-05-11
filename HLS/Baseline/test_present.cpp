#include "present.hpp"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

block_size golden_cipher_128[5] = { 0x48beec30145c3c34, 0x95ba1ece710dc9fa,
		0xaee42210dc48f3da, 0x8b0cd3aff2436fcd, 0x15e0a3f4cda33bd9 };
block_size golden_cipher_80[5] = { 0xf271bec24b39e83f, 0xf62cdd54b491ef90,
		0x4b16df1a3c60b80a, 0x5cebc7f8e666bccf, 0xc6304cbb8615e3f1 };
block_size plain_text[5] = { 0x797368656c646f6e, 0x73616e646965676f,
		0x6368657363616b65, 0x746f6d6a65727279, 0x6861636b726d616e };

//block_size key_high = 0xdb5490480f1e2d3c;
key_size key_high = 0x2d3c;
block_size key_low = 0x4b5a6978afed09a2;

int main() {
	int success = 0;
	block_size cipher[5];
	printf("The key is %x%llx\n", key_high, key_low);
	for (int i = 0; i < 5; i++) {
		present_encrypt(key_high, key_low, plain_text[i], &cipher[i]);
		printf(
				"The plain text is %llx, the golden cipher is %llx\n and the computed cipher is %llx\n",
				plain_text[i], golden_cipher_80[i], cipher[i]);
		if (cipher[i] == golden_cipher_80[i]) {
			success = success + 1;
		}
	}
	if (success == 5) {
		return 0;
	} else {
		return 1;
	}
}

