/* Cristina Nita, 2019 - SHA Project - Padding
** Secure Hash Algorithm, 256 bit version (SHA256)
** - https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977
** Source code adapted from
** - Unions:
**      * https://web.microsoftstream.com/video/78dc0c8d-a017-48c8-99da-0714866f35cb
** - Padding:
**      * 
** - Error Fixing:
**      * 
*/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

/* In this case the union is used 
** to read file in blocks of 512 bits.
** Unions are like structures (structs)
** but can only store one value at a time,
** everything is stored in the same location.
** Only used in variables related to each other
** that might have different types.
*/
union msgBlock{
  uint8_t e[64];                          // 8  bits(type) * 64 = 512
  uint32_t t[16];                         // 32 bits(type) * 16 = 512
  uint64_t s[8];                          // 64 bits(type) * 8  = 512
};

int main(int argc, char *argv[]){ 
  FILE* fp = fopen(argv[1], "r");         // reads a file
  union msgBlock M;                       // initialization of union message block
  uint64_t numBytes;                      // number of bytes -> number between 0 - 64
  uint64_t numBits = 0;                   // number of bits  -> all bits read

  /* fopen returns 0, the NULL pointer, on failure */
  /* Source code
  ** - https://stackoverflow.com/questions/9449295/opening-a-fp-from-command-line-arguments-in-c
  */
  if (fp == 0 )
  {
    printf( "Could not open file\n" );
  } 
  else {

    while (!feof(fp)) {
      numBytes = fread(M.e, 1, 64, fp);
      numBits += numBytes * 8;      
      // printf("Bytes: %2llu\n", numBytes);  // shows the number of bytes with padding

      if (numBytes <= 64-9) {
        printf("Block with less than 56 bytes! \n");
        // M.e[numBytes] = 0x01;          // right most position
        M.e[numBytes] = 0x80;             // left most position
        
        while (numBytes <= 64-9 ){
          numBytes += 1;
          M.e[numBytes] = 0x00;           // add k amount of 0's before appending
        } // while
        M.s[7] = numBits;

      } // if

    } // while

    fclose(fp);

    for (int i = 0; i < 65; i++) {
      printf("%x ", M.e[i]);
    }

    printf("\n");
  } // if.. else
	return 0;
}
