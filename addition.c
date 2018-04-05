#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj_coord.h"

// Weierstrass equation y^2 = x^3 + ax + b

// test values
//#define P 62CE5177412ACA899CF5
//#define A 39C95E6DDDB1BC45733C
//#define B 1F16D880E89D5A1C0ED1


proj_coord add(proj_coord a, proj_coord b) {
	proj_coord result;

	return result;
}

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
	number c = addition(a,b);
	printf("addMont of %s and %s equals %s\n", a_rep.digits, argv[2], toChar(c).digits);
	//number c = getInverse(a);
	//printf("inverse of %s equals %s\n", a_rep.digits, toChar(c).digits);

	return 0;
}