#include "present.hpp"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	int success = 0;
	int number_of_testcases = 7;
	uint64_t cipher, golden_cipher, plain_text, key_low;
	uint16_t key_high;
	block_t t_cipher, t_golden, t_plain, t_low;
	block_t t_high;
	FILE *fp = fopen("out.gold.dat", "r");
	for (int i = 0; i < number_of_testcases; i++) {
		fscanf(fp, "%4hX%16llX%16llX%16llX", &key_high, &key_low, &plain_text,
				&golden_cipher);
		t_golden.data = golden_cipher;
		t_plain.data = plain_text;
		t_low.data = key_low;
		t_high.data = key_high;
		present_encrypt(&t_high, &t_low, &t_plain, &t_cipher);
		cipher = t_cipher.data;
		printf(
				"The key is %04hX%016llX, plain text is %016llX, golden cipher is %016llX and the computed cipher is %016llX\n",
				key_high, key_low, plain_text, golden_cipher, cipher);
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
