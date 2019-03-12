// Author: Cristina Nita 2019 - Practical Exercise 1 from Theory of Algorithms Labs
#include <stdio.h>

int isPrime(unsigned int testPrime){
	unsigned int i;

	// prime numbers start at 2, the for loop continues until the number inputed is bigger than i
	for (i = 2; i < testPrime ; i++){
		// it checks if the testPrime number is divisible by any number between 2 and testPrime - 1
		// if not, the number is prime, otherwise it's not
		if (testPrime % i == 0 ){
			return 0; // returns 0 when no error
		}
	}

}

int main(int argc,char *argv[]){
	unsigned int test;

	// input for the number to be tested
	printf("Enter a number: ");
	scanf("%d", &test);

	// prints out whether the number is prime or n ot
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

