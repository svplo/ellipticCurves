#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj_coord.h"

// Weierstrass equation y^2 = x^3 + ax + b

// test values
#define x_P "315D4B201C208475057D"
#define y_P "035F3DF5AB370252450A"
#define x_Q "0679834CEFB7215DC365"
#define y_Q "4084 BC50388C 4E6FDFAB"

int main(int argc, char **argv) {
	if (argc != 3) {
		puts("need two numbers!\n");
		return 0;
	}
	char *first_number = argv[1]; // e.g. ABCDEF0123456789
	char *second_number = argv[2];

	number a = fromChar(first_number, strlen(first_number));
	number_rep a_rep = toChar(a);
	printf("before %s, after %s\n", argv[1], a_rep.digits);
	number b = fromChar(second_number, strlen(second_number));
	//number a1 = toMontgomery(a);
	//number b1 = toMontgomery(b);
	//printf("a1 %s and b1 %s .\n", toChar(a1).digits, toChar(b1).digits);
	//number a1 = multMontgomery(toMontgomery(a), toMontgomery(b));
	number a1 = multMontgomery(a, b);
	printf("multMont of %s and %s is %s \n", toChar(toMontgomery(a)).digits, toChar(toMontgomery(b)).digits, toChar(a1).digits);
	//printf("Mont of %s and %s \n", toChar(toMontgomery(a)).digits, toChar(toMontgomery(b)).digits);
	//number c = getInverse(a);
	//printf("inverse of %s equals %s\n", a_rep.digits, toChar(c).digits);

	return 0;
}
