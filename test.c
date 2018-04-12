#include <stdio.h>
#include "inttypes.h"


// Weierstrass equation y^2 = x^3 + ax + b

// test values
//#define P 62CE5177412ACA899CF5
//#define A 39C95E6DDDB1BC45733C
//#define B 1F16D880E89D5A1C0ED1

int main(int argc, char **argv) {
	uint8_t a = 17;

	printf("%d \n", (a&((1 <<7) >> 7)));
	//number c = getInverse(a);
	//printf("inverse of %s equals %s\n", a_rep.digits, toChar(c).digits);

	return 0;
}
