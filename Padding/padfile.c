/*  Cristina Nita, 2019 - SHA Project - Padding
** Secure Hash Algorithm, 256 bit version (SHA256)
** - https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977
** Source code adapted from
** - Unions:
**      * https://web.microsoftstream.com/video/78dc0c8d-a017-48c8-99da-0714866f35cb
** - Padding:
**      * https://web.microsoftstream.com/video/9daaf80b-9c4c-4fdc-9ef6-159e0e4ccc13
** - Error Fixing:
**      * https://web.microsoftstream.com/video/200e71ec-1dc1-47a4-9de8-6f58781e3f38
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
    uint8_t e[64];                                    // 8  bits(type) * 64 = 512
    uint32_t t[16];                                   // 32 bits(type) * 16 = 512
    uint64_t s[8];                                    // 64 bits(type) * 8  = 512
};

/* READ     = 0
** PAD0     = 1
** PAD1     = 2
** FINISH   = 3
*/
enum status {READ, PAD0, PAD1, FINISH};             // status of file read

int main(int argc, char *argv[]){ 
    FILE* fp = fopen(argv[1], "r");                 // reads a file
    union msgBlock M;                               // initialization of union message block
    uint64_t numBytes;                              // number of bytes -> number between 0 - 64
    uint64_t numBits = 0;                           // number of bits  -> all bits read
    enum status S = READ;                           // initialization of the enum status

    /* fopen returns 0, the NULL pointer, on failure */
    /* Source code
    ** - https://stackoverflow.com/questions/9449295/opening-a-fp-from-command-line-arguments-in-c
    */
    if (fp == 0 )
    {
        printf( "Could not open file\n" );
    } else {

        while (S == READ) {
            numBytes = fread(M.e, 1, 64, fp);
            numBits += numBytes * 8;      
            // printf("Bytes: %2llu\n", numBytes);  // shows the number of bytes with padding

            if (numBytes <= 64-9) {
                printf("Block with less than 55 bytes! \n");
                // M.e[numBytes] = 0x01;            // first byte in M that hasn't been overriden
                                                    // -> right most position
                M.e[numBytes] = 0x80;               // first byte in M that hasn't been overriden
                                                    // -> left most position

                while (numBytes <= 64-9 ){
                    numBytes += 1;
                    M.e[numBytes] = 0x00;             // add k amount of 0s before appending
                } // while
                M.s[7] = numBits;
                S = FINISH;

            } else if (numBytes < 64) {
                S = PAD0;                           // it aknowledges a message block containing all 0s is needed
                M.e[numBytes] = 0x80;

                while (numBytes < 64) {
                    numBytes += 1;
                    M.e[numBytes] = 0x00;           // padd with 0s
                } // while
            } else if (feof(fp)) {
                S = PAD1;
            } // if.. else if

        } // while

        fclose(fp);

        for (int i = 0; i < 65; i++) {
            printf("%x ", M.e[i]);
        }

        printf("\n");
    } // if.. else
    return 0;
}
