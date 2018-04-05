#include "inttypes.h"
#include <assert.h>

#define DIGITS 20

struct number {
	uint8_t val[DIGITS];
};

struct number_rep {
	char digits[DIGITS + 1];
};

typedef struct number number;
typedef struct number_rep number_rep;

number addition(number, number);
number addMont(number, number);
number multMont(number, number);
number multiplication(number, number);

/** NUMBER FORMATTING */
number fromChar(char *string, int size) {
	number result;
	for (int i = size - 1, j = 0; i >= 0; --i, ++j) {
		char c = string[i];
		if (48 <= c && c <= 57) {
			result.val[j] = c - 48;
		} else if (65 <= c && c <= 70) {
			result.val[j] = c - 65 + 10;
		} else if (97 <= c && c <= 102) {
			result.val[j] = c - 97 + 10;
		} else {
			assert(0);
		}
	}
	for (int j = size; j < DIGITS; ++j) {
		result.val[j] = 0;
	}
	return result;
};

number_rep toChar(number a) {
	number_rep result;
	for (int i = DIGITS - 1, j = 0; i >= 0; --i, ++j) {
		uint8_t c = a.val[i];
		if (0 <= c && c <= 9) {
			result.digits[j] = c + 48;
		} else {
			result.digits[j] = c + 65 - 10;
		}
	};
	result.digits[DIGITS] = 0;
	return result;
};

/** NUMBER ARITHMETIC */
// true = 1
// false = 0
uint8_t isEqual (number a, number b){
	for(int i = DIGITS - 1; i >= 0; --i){
		if(a.val[i] != b.val[i]){
			return 0;
		}
	}
	return 1;
}

uint8_t isGreaterEqual(number a, number b){
	for(int i = DIGITS - 1; i >= 0; --i){
		if(a.val[i] < b.val[i]){
			return 0;
		}
		if(a.val[i] > b.val[i]){
			return 1;
		}
	}
	return 1;
}

uint8_t isGreater(number a, number b){
	for(int i = DIGITS - 1; i >= 0; --i){
		if(a.val[i] > b.val[i]){
			return 1;
		}
	}
	return 0;
}

uint8_t isEven (number a){
	return a.val[0] % 2;
}

uint8_t endsWithZero (number a){
	return a.val[0] == 0;
}

number subtract(number a, number b){
	number result;
	return number;
}
