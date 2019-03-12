// Author: Cristina Nita 2019 - Practical Exercise 2 from Theory of Algorithms Labs
// Source code adapted from:
// - https://web.microsoftstream.com/video/e5e7f5d8-3d2f-4115-9eaa-d9b1d6a91c4e
#include <stdio.h>
#include <math.h>
#include <stdint.h>

// unsigned int array of prime numbers
unsigned int primes[] = {
   2,  3,   5,   7,   11,  13,  17,  19,  23,  29, 
   31, 37,  41,  43,  47,  53,  59,  61,  67,  71, 
  73, 79,  83,  89,  97,  101, 103, 107, 109, 113, 
 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 
 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 
 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 
 283, 293, 307, 311
};

int main(int args, char *argv[]){
  
   // variables
  long double fraction;
  long double cuberoot;
  long double multiplyFraction;
       
  for (int i = 0; i < 64; i++){ 
    cuberoot = cbrtl((long double) primes[i]);     // gets the long double cube root of the prime numbers in the primes array
    fraction = cuberoot - floor(cuberoot);         // the decimal points part of the cuberoot
    multiplyFraction = fraction * powl(2, 32);     // make the fractional part of the cube root a 32 bits numbers
                                                   // **can also use "0x100000000" instead of "pow(2, 32)**
    multiplyFraction = floorl(multiplyFraction);   // get rid of everything after the decimal point

    printf("%3d -> %Lf -> %Lf -> %08x\n", primes[i], cuberoot, fraction, (uint32_t)multiplyFraction);

  }
  
  return 0;
}

