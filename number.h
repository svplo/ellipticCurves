#include "inttypes.h"
#include <stdio.h>
#include <assert.h>

typedef int bool;
#define true 1
#define false 0

#define DIGITS 21
#define ZIFFER fromChar("00000000000000000004F", DIGITS) // 79
#define ZIFFERINT 79

#define ZERO fromChar("000000000000000000000", DIGITS)
#define ONE fromChar("000000000000000000001", DIGITS)
#define TWO fromChar("000000000000000000002", DIGITS)
#define THREE fromChar("000000000000000000003", DIGITS)
#define FOUR fromChar("000000000000000000004", DIGITS)
#define EIGHT fromChar("000000000000000000008", DIGITS)
#define INF fromChar("fffffffffffffffffffff", DIGITS)

// real values
#define PRIME fromChar("062CE5177412ACA899CF5", DIGITS)
#define RADIX fromChar("200000000000000000000", DIGITS)
#define RADIX2 fromChar("04d61511ea9c0fdaaf17c", DIGITS)
//#define PRIME "000000000000000000007"
//
// TEST values
//#define RADIX fromChar("000000000000000000064", DIGITS)
//#define PRIME fromChar("000000000000000000061", DIGITS)
//#define RADIX2 fromChar("000000000000000000009", DIGITS)

struct number {
	uint8_t val[DIGITS];
};

struct number_rep {
	char digits[DIGITS + 1];
};

typedef struct number number;
typedef struct number_rep number_rep;

number add(number, number);
number leftShift(number, uint8_t);
number subtract(number, number);

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
			return false;
		}
		if(a.val[i] > b.val[i]){
			return true;
		}
	}
	return true;
}

uint8_t isGreater(number a, number b){
	for(int i = DIGITS - 1; i >= 0; --i){
		if(a.val[i] < b.val[i]){
			return false;
		}
		if(a.val[i] > b.val[i]){
			return true;
		}
	}
	return false;
}

uint8_t isEven (number a){
	return a.val[0] % 2;
}

uint8_t endsWithZero (number a){
	return a.val[0] == 0;
}

number modulo(number a){
	number result = a;
	while(isGreaterEqual(result, PRIME)){
		result = subtract(result, PRIME);	
	}
	return result;
}

number addNoMod(number a, number b){
	number result;

	uint8_t carry = 0;
	for(int i = 0; i < DIGITS; ++i){
		result.val[i] = a.val[i] + b.val[i] + carry;
		carry = 0;
		if(result.val[i] >= 16){
			result.val[i] -= 16;
			carry = 1;
		}
	}
	return result;
}

number add(number a, number b){
	number result;

	number reducedA = modulo(a);
	number reducedB = modulo(b);

	uint8_t carry = 0;
	for(int i = 0; i < DIGITS; ++i){
		result.val[i] = reducedA.val[i] + reducedB.val[i] + carry;
		carry = 0;
		if(result.val[i] >= 16){
			result.val[i] -= 16;
			carry = 1;
		}
	}

	return modulo(result);
}

number bitMultNoMod(int bit, number a){
	number result = ZERO;

	for(int i = 0; i < bit; ++i){
		result = addNoMod(result,a);
	}	

	return result;
}

number bitMult(int bit, number a){
	number result = ZERO;

	for(int i = 0; i < bit; ++i){
		result = add(result,a);
	}	

	return result;
}

number divideByTwo(number a){
	number result = a;
	uint8_t carry = result.val[DIGITS - 1] & 1;
	result.val[DIGITS - 1] = result.val[DIGITS - 1] >> 1;

	for (int i = DIGITS - 2; i >= 0; --i){
		uint8_t carry2 = result.val[i] & 1;
		result.val[i] = result.val[i] >> 1;
		result.val[i] |= (carry << 3);
		carry = carry2;
	}

	return result;
}

number multNormal(number a, number b){
	number result = ZERO;

	for (int i = DIGITS - 1; i >= 0; --i){
		result = add(divideByTwo(result), bitMult(b.val[i], a));
		if(isGreaterEqual(result, PRIME)){
			result = subtract(result, PRIME);
		}
		if(isGreaterEqual(result, PRIME)){
			//reassigning result?
			result = subtract(result, PRIME);
		}
	}
		
	return result;
}

uint8_t getBit(uint8_t a, uint8_t b){
	return ((a & (1 << b)) >> b);	
}

number multMontgomery(number a, number b){
	number result = ZERO;

	for (int i = 0; i < ZIFFERINT; ++i){
		result = addNoMod(result, bitMultNoMod(getBit(a.val[i/4], i % 4), b));
		result = divideByTwo(addNoMod(result, bitMultNoMod(getBit(result.val[0], 0), PRIME)));
	}
	if(isGreaterEqual(result, PRIME)){
		result = subtract(result, PRIME);
	}
		
	return result;
}

number subtract(number a, number b){
	number result;

	uint8_t carry = 0;
	if(isGreater(b, a)){
		b = subtract(PRIME, b); 
		return add(a,b);
	}   
	for (int i = 0; i < DIGITS; ++i) {
	  if (a.val[i] < b.val[i] + carry) {
		  result.val[i] = (16 + a.val[i]) - b.val[i] - carry;
		  carry = 1;
	  } else {
		  result.val[i] = a.val[i] - b.val[i] - carry;
		  carry = 0;
	  }   
	}   

	return modulo(result);
}

number mult(number a, number b){
	number result = ZERO;

	for (int i = DIGITS - 1; i >= 0; --i){
		result = addNoMod(divideByTwo(result), bitMultNoMod(b.val[i], a));
	}
		
	return result;
}

number toMontgomery(number a){
	return multMontgomery(RADIX2, a);
}

//output gcd(a,b) > 1 (no inverse exists) or |b^(-1) * 2^n| mod a = mont(b^(-1)) mod a
number mmInverse(number a, number b){
	number u = a;
	number v = b;
	number r = ZERO;
	number s = ONE;
	number k = ZERO;
	while(isGreater(v, ZERO)){
		if(isEven(u)){
			u = divideByTwo(u);
			s = multNormal(s, TWO);
		} else if (isEven(v)){
			v = divideByTwo(v);
			r = multNormal(r, TWO);
		} else if (isGreater(u, v)){
			u = divideByTwo(subtract(u, v));
			r = add(r,s);
			s = multNormal(s, TWO);
		} else {
			v = divideByTwo(subtract(v, u));
			s = add(r,s);
			r = multNormal(r, TWO);
		}
		k = add(k, ONE);
	}
	if(! isEqual(u, ONE)){
		return INF; // a and b are not relatively prime
	}
	if(isGreaterEqual(r, a)){
		r = subtract(r,a);
	}
	while(isGreater(k, ZIFFER)){
		if(isEven(r)){
			r = divideByTwo(r);
		} else {
			r = divideByTwo(add(r,a));
		}
		k = subtract(k, ONE);
	}
	return subtract(a,r);
}

