#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj_coord.h"

// Weierstrass equation y^2 = x^3 + ax + b

// test values
#define x_P fromChar("0315D4B201C208475057D", DIGITS)
//#define y_P fromChar("0035F3DF5AB370252450A", DIGITS)
//#define x_Q fromChar("00679834CEFB7215DC365", DIGITS)
//#define y_Q fromChar("04084BC50388C4E6FDFAB", DIGITS)

//#define x_P fromChar("09f5D4B21fC208475057D", DIGITS)
#define y_P fromChar("09f4F3DFffB370252450A", DIGITS)
#define x_Q fromChar("09f7983fCEFB7215DC365", DIGITS)
#define y_Q fromChar("09ff4fff0388C4E6FDFAB", DIGITS)
int main(int argc, char **argv) {
//	if (argc != 3) {
//		puts("need two numbers!\n");
//		return 0;
//	}
//	char *first_number = argv[1]; // e.g. ABCDEF0123456789
//	char *second_number = argv[2];

//	number a = fromChar(first_number, strlen(first_number));
//	number_rep a_rep = toChar(a);
//	printf("before %s, after %s\n", argv[1], a_rep.digits);
//	number b = fromChar(second_number, strlen(second_number));
	//number a1 = toMontgomery(a);
	//number b1 = toMontgomery(b);
	//printf("a1 %s and b1 %s .\n", toChar(a1).digits, toChar(b1).digits);
	//number a1 = multMontgomery(toMontgomery(a), toMontgomery(b));
//	number a1 = subtract(a, b);
//	printf("dub of %s and %s is %s \n", toChar(a).digits, toChar(b).digits, toChar(a1).digits);
	//printf("Mont of %s and %s \n", toChar(toMontgomery(a)).digits, toChar(toMontgomery(b)).digits);
	//number c = getInverse(a);
	//printf("inverse of %s equals %s\n", a_rep.digits, toChar(c).digits);

	proj_coord P;
	proj_coord Q;
	printf("%s", toChar(RADIX2).digits);
	P.x = toMontgomery(x_P);
	P.y = toMontgomery(y_P);
	P.z = toMontgomery(ONE);
	Q.x = toMontgomery(x_Q);
	Q.y = toMontgomery(y_Q);
	Q.z = toMontgomery(ONE);
	proj_coord Z = pointDoubling(P);
	printf("Point addtion of x = %s y = %s z = %s  and x = %s y = %s z = %s is  x = %s y = %s z = %s \n", toChar(P.x).digits, toChar(P.y).digits, toChar(P.z).digits, toChar(Q.x).digits, toChar(Q.y).digits, toChar(Q.z).digits, toChar(Z.x).digits, toChar(Z.y).digits, toChar(Z.z).digits);
	return 0;
}
