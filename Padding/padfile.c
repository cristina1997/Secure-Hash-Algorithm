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

int main(int argc, char *argv[]){ 
	FILE* fp = fopen(argv[1], "r"); // do some error checking
    char c;
    /* fopen returns 0, the NULL pointer, on failure */
    /* Source code
    ** - https://stackoverflow.com/questions/9449295/opening-a-fp-from-command-line-arguments-in-c
    */
    if (fp == 0 )
    {
        printf( "Could not open file\n" );
    }
    else
    {
        printf("%c\n", fread(&c, 1, 1, f));

        fclose(fp);
    }
	return 0;
}