// Cristina Nita, 2019 - SHA Project
// Secure Hash Algorithm, 256 bit version (SHA256)
// - https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977
// Source code adapted from: 
// - https://web.microsoftstream.com/video/db7c03be-5902-4575-9629-34d176ff1366
#include <stdio.h>
#include <stdint.h>

// SHA computation
void sha256();

// Sigma computation - Section 4.1.2
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// ROTR_n(x) = ((x >> n) | (x << (32 - n)))  	
//		-> shift n positions to the right 
// 		-> and 32-n positions to the left
uint32_t rotr(uint32_t x, uint32_t n);

// SHR_n(x)  = (x >> n)
//		-> shift right n positions
uint32_t shr(uint32_t x, uint32_t n);

int main(int argc, char *argv[]){ 
	sha256();
	return 0;
}

void sha256(){
	uint32_t W[64]; 			// Message schedule - 64 bit words
	uint32_t a, b, c, d, e, f, g, h; 	// Working variables
	uint32_t T1, T2;			// Temporary variables 

	// Hash Value - Section 5.3.3
	uint32_t H[8] = {
		0x6a09e667, 
		0xbb67ae85, 
		0x3c6ef372, 
		0xa54ff53a, 
		0x510e527f, 
		0x9b05688c, 
		0x1f83d9ab, 
		0x5be0cd19		
	};

	uint32_t M[16];				// Message block

	// Loops through the first 16 elements of W[]
	for (int t = 0; t < 16; t++)
		W[t] = M[t];

	// Loops through the next 48 elements of W[]
	for (int t = 16; t < 64; t++)
		sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
}


uint32_t sig0(uint32_t x){
	// ROTR7(x)   ^  ROTR18(x)  ^  SHR3(x) 
	
} 
uint32_t sig1(uint32_t x){
	// ROTR17(x)  ^  ROTR19(x)  ^  SHR10(x)
}

