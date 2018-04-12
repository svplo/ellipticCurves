#include "inttypes.h"
#include <assert.h>

typedef int bool;
#define true 1
#define false 0

#define ZERO "000000000000000000000"
#define TWO "000000000000000000002"
#define DIGITS 21
#define RADIX "80000000000000000000"
#define PRIME "062CE5177412ACA899CF5"

//#define RADIX "000000000000000000064"
//#define PRIME "000000000000000000061"
struct number {
	uint8_t val[DIGITS];
};

struct number_rep {
	char digits[DIGITS + 1];
};

typedef struct number number;
typedef struct number_rep number_rep;

number add(number, number);
number mult(number, number);
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
	number p = fromChar(PRIME, DIGITS);
	while(isGreaterEqual(result, p)){
		result = subtract(result, p);	
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
	number result = fromChar(ZERO, DIGITS);

	for(int i = 0; i < bit; ++i){
		result = addNoMod(result,a);
	}	

	return result;
}

number bitMult(int bit, number a){
	number result = fromChar(ZERO, DIGITS);

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
	number result = fromChar(ZERO, DIGITS);
	number p = fromChar(PRIME, DIGITS);

	for (int i = DIGITS - 1; i >= 0; --i){
		result = add(divideByTwo(result), bitMult(b.val[i], a));
		if(isGreaterEqual(result, p)){
			result = subtract(result, p);
		}
		if(isGreaterEqual(result, p)){
			//reassigning result?
			result = subtract(result, p);
		}
	}
		
	return result;
}

uint8_t getBit(uint8_t a, uint8_t b){
	return ((a & (1 << b)) >> b);	
}

number multMontgomery(number a, number b){
	number result = fromChar(ZERO, DIGITS);
	number p = fromChar(PRIME, DIGITS);

	uint8_t len = DIGITS * 4;
	bool br = false;
	for(int i = DIGITS - 1; i >= 0; --i){
		for(int j = 3; j >= 0; --j){
			if(((a.val[i] & (1 << j)) >> j) == 0){
				len--;
			} else {
				br = true;
				break;
			}
		}
		if(br){
			break;
		}
	}

	number t1;
	number t2;
	number t3;
	for (int i = 0; i < len; ++i){
		t3 = result;
		t2 = bitMultNoMod(getBit(a.val[i/4], i%4), b);
		t3 = addNoMod(t3, t2);
		uint8_t tt = getBit(t3.val[0], 0);
		t2 = bitMultNoMod(tt, p);
		t1 = addNoMod(t3, t2);
		t3 = divideByTwo(t1);
		result = addNoMod(result, bitMultNoMod(getBit(a.val[i/4], i % 4), b));
		result = divideByTwo(addNoMod(result, bitMultNoMod(getBit(result.val[0], 0), p)));
	}
	if(isGreaterEqual(result, p)){
		result = subtract(result, p);
	}
		
	return result;
}

number subtract(number a, number b){
	number result;
	number p = fromChar(PRIME, DIGITS);

	uint8_t carry = 0;
	if(isGreater(b, a)){
		b = subtract(p, b); 
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

number toMontgomery(number a){
	return multNormal(a, fromChar(RADIX, DIGITS));		
}
