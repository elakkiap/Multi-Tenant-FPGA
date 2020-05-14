#include "present.hpp"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	int success = 0;
	int number_of_testcases = 7;
	block_size cipher, golden_cipher, plain_text, key_low;
	key_size key_high;
	FILE *fp = fopen("out.gold.dat", "r");
	for (int i = 0; i < number_of_testcases; i++) {
		fscanf(fp, "%04hX%16llX%16llX%16llX", &key_high, &key_low, &plain_text, &golden_cipher);
		present_encrypt(key_high, key_low, plain_text, &cipher);
		printf("The key is %04hX%016llX, plain text is %016llX, golden cipher is %016llX and the computed cipher is %016llX\n", key_high, key_low, plain_text, golden_cipher, cipher);
		if (cipher == golden_cipher) {
			success = success + 1;
		}
	}
	fclose(fp);
	if (success == number_of_testcases) {
		return 0;
	} else {
		return 1;
	}
}
