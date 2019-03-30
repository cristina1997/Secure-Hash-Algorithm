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

/* 			ROTL_n(x) 
** SHIFT N POSITIONS TO THE LEFT
** AND 32-n POSITIONS TO THE RIGHT
**********************************
** 			ROTR_n(x) 
** SHIFT N POSITIONS TO THE RIGHT
** AND 32-n POSITIONS TO THE LEFT
**********************************
**			SHR_n(x) 
** SHIFT N POSITIONS TO THE LEFT
*/
#define rotl(x, n) ((x << n) | (x >> (32 - n)))
#define rotr	(x, n) ((x >> n) | (x << (32 - n)))
#define shr		(x, n) (x >> n)


#define Ch		(x, y, z) ((x & y) ^ (~(x) & z ))
#define Maj		(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define EP0		(x) (rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22))
#define EP1		(x) (rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25))
#define SIG_0 	(x) (rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3))
#define SIG_1	(x) (rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10))

/*
** 			ENDIAN_SWAP_UINT64
** CONVERTS 64 BIT INTEGERS TO BIG INTS
***************************************
** 			ENDIAN_SWAP_UINT32
** CONVERTS 32 BIT INTEGERS TO BIG INTS
*/
#define ENDIAN_SWAP_UINT64(x) ( \
    (( (x) &  0x00000000000000ff) << 56) | \
    (( (x) &  0x000000000000ff00) << 40) | \
    (( (x) &  0x0000000000ff0000) << 24) | \
    (( (x) &  0x00000000ff000000) <<  8) | \
    (( (x) &  0x000000ff00000000) >>  8) | \
    (( (x) &  0x0000ff0000000000) >> 24) | \
    (( (x) &  0x00ff000000000000) >> 40) | \
    (( (x) &  0xff00000000000000) >> 56))
#define ENDIAN_SWAP_UINT32(x) ( \
	((x) >> 24) | \
	(((x) & 0x00FF0000) >> 8) | \
	(((x) & 0x0000FF00) << 8) | \
	((x) << 24))

/* UNION
** - represents a message block
** - used to read file in blocks of 512 bits
** - like structures (structs)
** - can only store one value at a time
** - stored in the same location.
** - used in variables related to each other
**   that might have different types.
*/
union msgBlock{
    uint8_t  e[64];                                   // 8  bits(type) * 64 = 512
    uint32_t t[16];                                   // 32 bits(type) * 16 = 512
    uint64_t s[8];                                    // 64 bits(type) * 8  = 512
};

/* UNION
** - represents a message block
** - used to read file in blocks of 512 bits
** - like structures (structs)
** - can only store one value at a time
** - stored in the same location.
** - used in variables related to each other
**   that might have different types.
*/
struct temp {
	// Temporary variables 
	uint32_t TEMP1;	
	uint32_t TEMP2;	
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

void sha256(FILE *fp);									// SHA computation
int nextMsgBlock(FILE *fp, 								// PADDING computation
				union msgBlock *M, 
				enum status *S, 
				int *numBits);

int main(int argc, char *argv[]){ 

	FILE *fp = fopen(argv[1], "r");						// reads a file 
	FILE *fprint = fopen(argv[1], "r");					// reads a file 
	char fileContent;
		
	/* If no file to be opened is mentioned
	** let the user know that no file was mentioned.
	** Source code
	** - https://stackoverflow.com/questions/9449295/opening-a-fp-from-command-line-arguments-in-c
	*/
	if (fp == NULL) {
		printf("No file to be open mentioned.\n");
	}
	else {
		printf("\n\tFILE CONTENT: \n\t\t- ");
		 while((fileContent = fgetc(fprint)) != EOF) 
     		 printf("%c", fileContent);
		sha256(fp);										// run secure hash algorithm
	}

	fclose(fp);											// close the file

	return 0;
} // int main() method

int nextMsgBlock(FILE *fp, union msgBlock *M, enum status *S, int *numBits){ 
	int numBytes;										// number of bytes -> between 0 - 64

	// All message blocks are finished
	if (*S == FINISH){
		return 0;
	}
	
	/* IF a block full of padding is needed 
	** - then set first 56 bytes to 0 bits
	** - set the last 64 bits to the no. of bits in the file (big endian)
	** - Status == finished.
	********************************************************************
	** IF S was PAD1 then set the first bit of M to 1.
	** - PAD0 - first bit is 0
	** - PAD1 - first bit is 1
	*/
	if (*S == PAD0 || *S == PAD1) {
		for (int i = 0; i <= 64-9; i++)					// leaves 8 bytes at the end for the 64 bit integer
			M->e[i] = 0x00;								// padding the 448 bits with 0s


		M->s[7] = *numBits;       
		M->s[7] = ENDIAN_SWAP_UINT64(M->s[7]);
		*S = FINISH;

		
		if (*S == PAD1)
			M->e[0] = 0x80;  

		return 1;   
	} // if


   	// The file hasn't finished reading (S is equal to READ)    
	numBytes = fread(M->e, 1, 64, fp);
	*numBits += numBytes * 8;      


	// If less than 56 bytes is read then add padding
	if (numBytes <= 64-9) {
		// printf("Block with less than 55 bytes! \n");
		// M.e[numBytes] = 0x01;						// first byte in M that hasn't been overriden
														//	-> right most position
		M->e[numBytes] = 0x80;							// first byte in M that hasn't been overriden
														//	->	left most position
		
		while (numBytes <= 64-9){
			numBytes += 1;
			M->e[numBytes] = 0x00;						// add k amount of 0s before appending
		} // while

		M->s[7] = *numBits;								// append file size in bits (big endian) - 64 bit int
		M->s[7] = ENDIAN_SWAP_UINT64(M->s[7]);
		*S = FINISH;									// Status == finished

	} else if (numBytes < 64) {							// check if there's enough space for paddings
		*S = PAD0;										// it aknowledges a message block containing all 0s is needed
		M->e[numBytes] = 0x80;							// insert 1 bit in current block

		while (numBytes < 64) {				
			numBytes += 1;
			M->e[numBytes] = 0x00;						// padd the rest with 0s
		} // while
	} else if (feof(fp)) { 								// check if we're at the end of the file
		*S = PAD1;										// another message block with padding is needed
	} // if.. else if
	return 1;											// the function is called again
	
} // int nextMsgBlock() method

void sha256(FILE *fp){
	// SHA Calculation variables
	struct temp *ctxT;	
	uint32_t W[64];										// Message schedule - 64 bit words
	uint32_t a, b, c, d, e, f, g, h;					// Working variables
	
	// Padding Calculation variables
	union msgBlock M;									// current message block
  	enum status S = READ;								// message blocks status
  	int numBits = 0;									// number of bits read

	// Hash Value - Section 5.3.3
	uint32_t H[8] = {
		0x6a09e667, 	0xbb67ae85, 	0x3c6ef372, 	0xa54ff53a, 
		0x510e527f, 	0x9b05688c, 	0x1f83d9ab, 	0x5be0cd19		
	}; // H[8]

	// Constant for the hash computation - Section 4.2.2
	uint32_t K[64] = {
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
		// Loops through the first 16 elements of W[] - Step 1 Page 24
		for (int i = 0; i < 16; i++)
			W[i] = ENDIAN_SWAP_UINT32(M.t[i]);

		// Loops through the next 48 elements of W[] - Step 1 Page 24
		for (int i = 16; i < 64; i++)
			W[i] = SIG_1(W[i-2]) + W[i-7] + SIG_0(W[i-15]) + W[i-16];		

		// Initialize a, b, c, d, e - Step 2 Page 22
		a = H[0]; 		b = H[1]; 		c = H[2]; 		d = H[3]; 
		e = H[4]; 		f = H[5]; 		g = H[6]; 		h = H[7];
		
		// Step 3 - Page 23
		for (int i = 0; i < 64; i++) {
			ctxT->TEMP1 = h + EP1(e) + Ch(e, f, g) + K [i] + W[i];
			ctxT->TEMP2 = EP0(a) + Maj(a, b, c);
			h = g; 		g = f; 		f = e; 		e = d + ctxT->TEMP1;
			d = c; 		c = b; 		b = a;		a = ctxT->TEMP1 + ctxT->TEMP2;
		} // for
		
		// Step 4 - Page 23
		H[0] += a;		H[1] += b;		H[2] += c;		H[3] += d;
		H[4] += e;		H[5] += f;		H[6] += g;		H[7] += h;
	} // while
	
	printf("\n\tHASH CONTENT: \n\t\t- ");
	for (int i = 0; i < 8; i++)
		printf("%x ", H[i]);	
	
	printf("\n\n");
} // void sha256() method