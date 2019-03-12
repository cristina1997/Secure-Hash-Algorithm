#include <stdio.h>

int isPrime(unsigned int testPrime){
  unsigned int i;

  for (i = 2; i < testPrime ; i++){
    if (testPrime % i == 0 ){
	return 0; // returns 0 when no error
    }
  }

}

int main(int argc,char *argv[]){
  unsigned int test;

  printf("Enter a number: ");
  scanf("%d", &test);
   

  if (isPrime(test))
    printf("%d is prime.\n", test);	  
  else
    printf("%d is not prime.\n", test);

  printf("argc is %d\n", argc);
  for (int i = 0; i < argc; i++){
    printf("argv[%d] is %s\n", i, argv[i]);
  }

  return 0;
}

