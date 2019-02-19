#include <stdio.h>
#include <math.h>
#include <stdint.h>

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
  
  long double fraction;
  long double cuberoot;
  long double multiplyFraction;
       
  for (int i = 0; i < 64; i++){ 
    cuberoot = cbrtl((long double) primes[i]);
    fraction = cuberoot - floor(cuberoot);
    multiplyFraction = fraction * powl(2, 32);
    multiplyFraction = floorl(multiplyFraction);

    printf("%3d -> %Lf -> %Lf -> %08x\n", primes[i], cuberoot, fraction, (uint32_t)multiplyFraction);

  }

  
  return 0;
}

