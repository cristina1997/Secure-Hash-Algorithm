/* Cristina Nita, 2019 - SHA Project - No Padding
** Secure Hash Algorithm, 256 bit version (SHA256)
** - https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977
** Source code adapted from
** - SHA-256 Algorithm
** 		* Part 1:
** 			https://web.microsoftstream.com/video/db7c03be-5902-4575-9629-34d176ff1366
** 		* Part 2:
** 			https://web.microsoftstream.com/video/2a86a2ac-aafb-46e0-a278-a3faa1d13cbf
** - Unions:
**      * https://web.microsoftstream.com/video/78dc0c8d-a017-48c8-99da-0714866f35cb
** - Padding:
**      * https://web.microsoftstream.com/video/9daaf80b-9c4c-4fdc-9ef6-159e0e4ccc13
** - Error Fixing:
**      * https://web.microsoftstream.com/video/200e71ec-1dc1-47a4-9de8-6f58781e3f38
** - Pointers:
** 		* https://web.microsoftstream.com/video/f823809a-d8df-4e12-b243-e1f8ed76b93f
*/
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>


/* Union
** - represents a message block
** - used to read file in blocks of 512 bits
** - like structures (structs)
** - can only store one value at a time
** - stored in the same location.
** - used in variables related to each other
**   that might have different types.
*/
union msgBlock{
    uint8_t  e [64];                                   // 8  bits(type) * 64 = 512
    uint32_t t [16];                                   // 32 bits(type) * 16 = 512
    uint64_t s [8];                                    // 64 bits(type) * 8  = 512
};

/* Flag for File Read
** - READ     = 0
** - PAD0     = 1
** - PAD1     = 2
** - FINISH   = 3
*/
enum status {
	READ, 
	PAD0, 
	PAD1, 
	FINISH,
};             


/** 
***	Declaration of methods
**/
// SHA computation
void sha256(FILE *fp);
int nextMsgBlock(FILE *fp, union msgBlock *M, enum status *S, int *numBits);

// Sigma 0 and 1 computation - Section 4.1.2
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// ROTR computation
uint32_t rotr(uint32_t n, uint32_t x);
// SHR computation
uint32_t shr(uint32_t n, uint32_t x);

// SHA-256 Functions - Section 4.1.2
uint32_t SIG_0(uint32_t x);
uint32_t SIG_1(uint32_t x);
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);     

int main(int argc, char *argv[]){ 

	FILE *fp = fp  = fopen(argv [1], "r");		// reads a file 
		
 	/* If no file to be opened is mentioned
	** let the user know that no file was mentioned.
  	** Source code
    ** - https://stackoverflow.com/questions/9449295/opening-a-fp-from-command-line-arguments-in-c
    */
  if (fp == NULL)
      printf("No file to be open mentioned.\n");
  else 
	  sha256(fp);							// run secure hash algorithm
   
    fclose(fp);								// close the file

	return 0;
} // int main() method

int nextMsgBlock(FILE *fp, union msgBlock *M, enum status *S, int *numBits){ 
	int numBytes;						// number of bytes -> between 0 - 64

	// All message blocks are finished
	if (*S == FINISH){
		return 0;
	}
	
	/* If a block full of padding is needed 
	** then set first 56 bytes to 0 bits
	** set the last 64 bits to the no. of bits in the file (big endian)
	** Status == finished.
	** If S was PAD1 then set the first bit of M to 1.
	** - PAD0 - first bit is 0
	** - PAD1 - first bit is 1
	*/
	if (*S == PAD0 || *S == PAD1) {
		for (int i = 0; i <= 64-9; i++)		// leaves 8 bytes at the end for the 64 bit integer
			M -> e [i] = 0x00;				// padding the 448 bits with 0s


		M -> s [7] = *numBits;       
		*S = FINISH;

		
		if (*S == PAD1)
			M -> e [0] = 0x80;  

		return 1;   
	} // if


   	// The file hasn't finished reading (S is equal to READ)    
	numBytes = fread(M -> e, 1, 64, fp);
	*numBits += numBytes * 8;      

	// If less than 56 bytes is read then add padding
	if (numBytes <= 64-9) {
		printf("Block with less than 55 bytes! \n");
		// M.e [numBytes] = 0x01;			// first byte in M that hasn't been overriden
											// -> right most position
		M -> e [numBytes] = 0x80;			// first byte in M that hasn't been overriden
											// -> left most position
		
		while (numBytes <= 64-9){
			numBytes += 1;
			M -> e [numBytes] = 0x00;		// add k amount of 0s before appending
		} // while

		M -> s [7] = *numBits;				// append file size in bits (big endian) - 64 bit int
		*S = FINISH;						// Status == finished

	} else if (numBytes < 64) {				// check if there's enough space for paddings
		*S = PAD0;							// it aknowledges a message block containing all 0s is needed
		M -> e [numBytes] = 0x80;			// insert 1 bit in current block

		while (numBytes < 64) {				
			numBytes += 1;
			M -> e [numBytes] = 0x00;		// padd the rest with 0s
		} // while
	} else if (feof(fp)) { 					// check if we're at the end of the file
		*S = PAD1;							// another message block with padding is needed
	} // if.. else if
	return 1;								// the function is called again
	
} // int nextMsgBlock() method

void sha256(FILE *fp){
	// SHA Calculation variables
	uint32_t W [64];						// Message schedule - 64 bit words
	uint32_t a, b, c, d, e, f, g, h;		// Working variables
	uint32_t T1, T2;						// Temporary variables 
	
	// Padding Calculation variables
	union msgBlock M;						// current message block
  	enum status S = READ;					// message blocks status
  	int numBits = 0;					// number of bits read

	// Hash Value - Section 5.3.3
	uint32_t H [8] = {
		0x6a09e667, 	0xbb67ae85, 	0x3c6ef372, 	0xa54ff53a, 
		0x510e527f, 	0x9b05688c, 	0x1f83d9ab, 	0x5be0cd19		
	}; // H[8]

	// Constant for the hash computation - Section 4.2.2
	uint32_t K [] = {
		0x428a2f98, 	0x71374491, 	0xb5c0fbcf, 	0xe9b5dba5, 
		0x3956c25b, 	0x59f111f1, 	0x923f82a4, 	0xab1c5ed5, 
		0xd807aa98, 	0x12835b01, 	0x243185be, 	0x550c7dc3, 
		0x72be5d74, 	0x80deb1fe, 	0x9bdc06a7, 	0xc19bf174, 
		0xe49b69c1, 	0xefbe4786, 	0x0fc19dc6, 	0x240ca1cc, 
		0x2de92c6f, 	0x4a7484aa, 	0x5cb0a9dc, 	0x76f988da, 
		0x983e5152, 	0xa831c66d, 	0xb00327c8, 	0xbf597fc7, 
		0xc6e00bf3, 	0xd5a79147, 	0x06ca6351, 	0x14292967, 
		0x27b70a85, 	0x2e1b2138, 	0x4d2c6dfc, 	0x53380d13, 
		0x650a7354, 	0x766a0abb, 	0x81c2c92e, 	0x92722c85,
		0xa2bfe8a1, 	0xa81a664b, 	0xc24b8b70, 	0xc76c51a3, 
		0xd192e819, 	0xd6990624, 	0xf40e3585, 	0x106aa070, 
		0x19a4c116, 	0x1e376c08, 	0x2748774c, 	0x34b0bcb5, 
		0x391c0cb3, 	0x4ed8aa4a, 	0x5b9cca4f, 	0x682e6ff3, 
		0x748f82ee, 	0x78a5636f, 	0x84c87814, 	0x8cc70208, 
		0x90befffa, 	0xa4506ceb, 	0xbef9a3f7, 	0xc67178f2
	}; // K[]

	// Loop through message blocks as per page 22
	while (nextMsgBlock(fp, &M, &S, &numBits)){
		
		// Hash Computation - Section 6.4.2
		// Loops through the first 16 elements of W [] - Step 1 Page 24
		for (int i = 0; i < 16; i++)
			W  [i] = M.t  [i];

		// Loops through the next 48 elements of W [] - Step 1 Page 24
		for (int i = 16; i < 64; i++)
			W  [i] = sig1(W [i-2]) + W [i-7] + sig0(W [i-15]) + W [i-16];
				
		// Initialize a, b, c, d, e - Step 2 Page 22
		a = H [0]; b = H [1]; c = H [2]; d = H [3]; 
		e = H [4]; f = H [5]; g = H [6]; h = H [7];
		
		// Step 3 - Page 23
		for (int i = 0; i < 64; i++) {
			T1 = h * SIG_1(e) + Ch(e, f, g) + K  [i] + W  [i];
			T1 = SIG_0(a) * Maj(a, b, c);
			h = g; g = f; f = e;
			e = d + T1;
			d = c; c = b; b = a;
			a = T1 + T2;
		} // for
		
		// Step 4 - Page 23
		H [0] = a + H [0]; 	H [1] = b + H [1];	H [2] = c + H [2];	H [3] = d + H [3];
		H [4] = e + H [4];	H [5] = f + H [5];	H [6] = g + H [6];	H [7] = h + H [7];
	} // while
	

	for (int i = 0; i < 8; i++)
		printf("%x \n", H [i]);	
	
} // void sha256() method

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

uint32_t SIG_0(uint32_t x){
	return rotr(2, x) ^ rotr(13, x) ^ rotr(22, x);
}

uint32_t SIG_1(uint32_t x){
	return rotr(6, x) ^ rotr(11, x) ^ rotr(25, x);;
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
	return (x & y) ^ ((!x) & z);
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
	return (x & y) ^ (x & z) ^ (y & z);
}



