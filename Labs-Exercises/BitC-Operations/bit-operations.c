#include <stdio.h>
#include <stdint.h>

void binprint(uint_32_t x){
	uint_32_t one = 1;
	
	for (int i = 0; i < 32; i++)
		if ((one << (31 - i)) & x)
			printf("1");
		else
			printf("0");
	}
	
}

uint_32_t rotl(uint_32_t x, int n){
	return ((x << n) | (x >> (32 - n)));
}

uint_32_t rotr(uint_32_t x, int n){
	return ((x >> n) | (x << (32 - n)));
}

int main (int argc, char *argv[]){

	uint_32_t a = 1;
	uint_32_t b = 2;
	
	// Hex
	printf(" a: %08x\n", a);	
	printf(" b: %08x\n", b);	
	
	printf(" &: %08x\n", (a&b));	
	printf(" |: %08x\n", (a|b));
	printf(" ^: %08x\n", (a^b));	
	printf(" ~: %08x\n", (~a));	
	printf(" <<: %08x\n", (a<<1));	
	printf(" >>: %08x\n", (a>>1));
	
	
	// Binary
	printf("\n a: "); binprint(a);
	printf("\n b: "); binprint(b);
	
	printf("\n &: "); binprint(a&b);
	printf("\n |: "); binprint(a|b);
	printf("\n ^: "); binprint(a^b);
	printf("\n ~: "); binprint(~a);
	printf("\n <<: "); binprint(a<<1);
	printf("\n >>: "); binprint(a>>1);
	
	return 0	
}


