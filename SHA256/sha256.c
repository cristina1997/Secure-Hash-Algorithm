/* Cristina Nita, 2019 - SHA Project
** Secure Hash Algorithm, 256 bit version (SHA256)
** - https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977
** Source code adapted from: 
** - https://web.microsoftstream.com/video/db7c03be-5902-4575-9629-34d176ff1366
*/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

// SHA computation
void sha256();

// Sigma 0 and 1 computation - Section 4.1.2
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// ROTR computation
uint32_t rotr(uint32_t n, uint32_t x);
// SHR computation
uint32_t shr(uint32_t n, uint32_t x);


// SHA-256 Functions - Section 4.1.2
uint32_t SIG_0(uint32_t X);
uint32_t SIG_1(uint32_t X);
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

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
		W[t] = sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
	
	// Initialize a, b, c, d, e - Step 2 Page 22
	a = H[0]; b = H[1]; c = H[2]; d = H[3]; 
	e = H[4]; f = H[5]; g = H[6]; h = H[7];
	
	// Step 3 - Page 23
	for (int t = 0; t < 64; t++) {
		T1 = h * SIG_1(e) + Ch(e, f, g) + K[t] + W[t];
		T1 = SIG_0(a) * Maj(a, b, c);
		h = g; g = f; f = e;
		e = d + T1;
		d = c; c = b; b = a;
		a = T1 + T2;
	}	
	
	// Step 4 - Page 23
	H[0] = a + H[0];
	H[1] = b + H[1];
	H[2] = c + H[2];	
	H[3] = d + H[3];
	H[4] = e + H[4];
	H[5] = f + H[5];
	H[6] = g + H[6];
	H[7] = h + H[7];
	
}

/************* ROTR_n(x) **************/
/*** shift n positions to the right ***/
/*** and 32-n positions to the left ***/
uint32_t rotr(uint32_t x, uint32_t n){
	return ((x >> n) | (x << (32 - n)));
}

/********** SHR_n(x) ***********/
/*** shift right n positions ***/
uint32_t shr(uint32_t x, uint32_t n){	
	return (x >> n);
}

/**  ROTR7(x)   XOR  ROTR18(x)  XOR  SHR3(x)  **/
uint32_t sig0(uint32_t x){
	return (rotr(7, x) ^  rotr(18, x) ^ shr(3, x));
} 

/**  ROTR17(x)  XOR  ROTR19(x)  XOR  SHR10(x)  **/
uint32_t sig1(uint32_t x){
	return (rotr(17, x) ^  rotr(19, x) ^ shr(10, x));
}

uint32_t SIG_0(uint32_t X){
	return rotr(2, x) ^ rotr(13, x) ^ rotr(22, x);
}

uint32_t SIG_1(uint32_t X){
	return rotr(6, x) ^ rotr(11, x) ^ rotr(25, x);;
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
	return (x & y) ^ ((!x) & z);
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
	return (x & y) ^ (x & z) ^ (y & z);
}


