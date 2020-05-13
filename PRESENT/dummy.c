#include<stdio.h>
#include<stdint.h>

int main(){
	FILE *fp = fopen("out.gold.dat", "rb");
	uint16_t key_high;
	uint64_t key_low, plain_text, golden_cipher;
	for(int i=0; i<7; i++)
	{
	fscanf(fp,"%04hx%016lx%016lx%016lx", &key_high, &key_low, &plain_text, &golden_cipher);
	printf("%04hx%016lx %016lx %016lx\n", key_high, key_low, plain_text, golden_cipher);
	}
	fclose(fp);
	return 0;
}

