// Author: Cristina Nita 2019 - Practical Exercise 3 from Theory of Algorithms Labs
// Source code adapted from:
// - https://web.microsoftstream.com/video/c24ff5f4-e5e1-4747-af8d-c2c4892856e3
#include <stdio.h>
#include <stdint.h>

// it convers numbers from hexadecimal values to binary values
void binprint(uint32_t x){
	uint32_t one = 1;
	int i;
	
	for (i = 0; i < 32; i++) {
		if ((one << (31 - i)) & x)
			printf("1");
		else
			printf("0");
	}
	
}

// ROTL_n(x) 
//	-> shift n positions to the left 
//	-> and 32-n positions to the right
uint32_t rotl(uint32_t x, int n){
	return ((x << n) | (x >> (32 - n)));
}

// ROTR_n(x) 
//	-> shift n positions to the right 
//	-> and 32-n positions to the left
uint32_t rotr(uint32_t x, int n){
	return ((x >> n) | (x << (32 - n)));
}

int main (int argc, char *argv[]){

	uint32_t a = 1;
	uint32_t b = 2;
	
	// Values printed as hexadecimal numbers
	printf(" a: %08x\n", a); 		// value of a as hexadecimal numbers
	printf(" b: %08x\n", b);		// value of b as hexadecimal numbers
	
	printf(" &: %08x\n", (a&b));		// a AND b
	printf(" |: %08x\n", (a|b));		// a OR b
	printf(" ^: %08x\n", (a^b));		// a XOR b
	printf(" ~: %08x\n", (~a));		// NOT a
	printf(" <<: %08x\n", (a<<1));		// shifts a 1 position to the left
	printf(" >>: %08x\n", (a>>1));		// shifts a 1 position to the right
	
	
	// Values printed as binary numbers
	printf("\n a: "); binprint(a); 		// value of a as binary numbers
	printf("\n b: "); binprint(b); 		// value of b as binary numbers
	
	printf("\n &: "); binprint(a&b);	// a AND b
	printf("\n |: "); binprint(a|b);	// a OR b
	printf("\n ^: "); binprint(a^b);	// a XOR b
	printf("\n ~: "); binprint(~a);		// NOT a
	printf("\n <<: "); binprint(a<<1);	// shifts a 1 position to the left
	printf("\n >>: "); binprint(a>>1);	// shifts a 1 position to the right
	
	return 0;
}


