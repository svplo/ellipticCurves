#include "number.h"

struct proj_coord {
	number x, y, z;
};
typedef struct proj_coord proj_coord;
//test values
#define A fromChar("039C95E6DDDB1BC45733C", DIGITS)
#define B fromChar("01F16D880E89D5A1C0ED1", DIGITS)
//#define A fromChar("000000000000000000003",DIGITS)
//#define B fromChar("000000000000000000011",DIGITS)

uint8_t equalCoord(proj_coord a, proj_coord b){
	if(!isEqual(a.x, b.x)){
		return 0;
	}
	if(!isEqual(a.y, b.y)){
		return 0;
	}
	if(!isEqual(a.z, b.z)){
		return 0;
	}
	return 1;
}

proj_coord pointDoubling(proj_coord c){
	proj_coord result;
	number T1 = c.x;
	number T2 = c.y;
	number T3 = c.z;
	if(isEqual(T2, ZERO) || isEqual(T3, ZERO)){
		result.x = ONE;
		result.y = ONE;
		result.z = ZERO;
		// return infinite point
		return result;	
	}
	number pMinus3 = subtract(PRIME, THREE);
	number T4;	
	number T5;	
	if(isEqual(A, pMinus3)){
		T4 = multMontgomery(T3, T3);
		T5 = subtract(T1, T4);
		T4 = add(T1, T4);	
		T5 = multMontgomery(T4, T5);
		T4 = multMontgomery(THREE, T5);
	} else {
		T4 = A;
		T5 = multMontgomery(T3, T3);
		T5 = multMontgomery(T5, T5);
		T5 = multMontgomery(T4, T5);
		T4 = multMontgomery(T1, T1);
		T4 = multMontgomery(THREE, T4);
		T4 = add(T4, T5);	
	}
	T3 = multMontgomery(T2, T3);
	T3 = multMontgomery(TWO, T3);
	T2 = multMontgomery(T2, T2);
	T5 = multMontgomery(T1, T2);
	T5 = multMontgomery(FOUR, T5);
	T1 = multMontgomery(T4, T4);
	T1 = subtract(T1, multMontgomery(TWO, T5));
	T2 = multMontgomery(T2, T2);
	T2 = multMontgomery(EIGHT, T2);
	T5 = subtract(T5, T1);
	T5 = multMontgomery(T4, T5);
	T2 = subtract(T5, T2);
	result.x = T1;
	result.y = T2;
	result.z = T3;
	return result;
}

proj_coord pointAddition(proj_coord g, proj_coord h){
	assert(!isEqual(ZERO, g.z) && !isEqual(ZERO, h.z));
	proj_coord result;

	number T1 = g.x;
	number T2 = g.y;
	number T3 = g.z;
	number T4 = h.x;
	number T5 = h.y;
	number T6;
	number T7;
	if(!isEqual(h.z, ONE)){
		T6 = h.z;
		T7 = multMontgomery(T6, T6);
		T1 = multMontgomery(T1, T7);
		T7 = multMontgomery(T6, T7);
		T2 = multMontgomery(T2, T7);
	}
	T7 = multMontgomery(T3,T3);
	T4 = multMontgomery(T4, T7);
	T7 = multMontgomery(T3, T7);
	T5 = multMontgomery(T5, T7);
	T4 = subtract(T1, T4);
	T5 = subtract(T2, T5);
	if(isEqual(T4, ZERO)){
		if(isEqual(T5, ZERO)){
			result.x = ZERO;
			result.y = ZERO;
			result.z = ZERO;
			return result;
		} else{
			result.x = ZERO;
			result.y = ZERO;
			result.z = ZERO;
			return result;
		}
	}

	T1 = subtract(multMontgomery(TWO, T1), T4);
	T2 = subtract(multMontgomery(TWO, T2), T5);
	if(!isEqual(h.z, ONE)){
		T3 = multMontgomery(T3, T6);
	}
	T3 = multMontgomery(T3, T4);
	T7 = multMontgomery(T4, T4);
	T4 = multMontgomery(T4, T7);
	T7 = multMontgomery(T1, T7);
	T1 = multMontgomery(T5, T5);
	T1 = subtract(T7, multMontgomery(TWO, T1));
	T5 = multMontgomery(T5, T7);
	T4 = multMontgomery(T2, T4);
	T2 = subtract(T5, T4);
	T2  = divideByTwo(T2);
	result.x = T1;
	result.y = T2;
	result.z = T3;

	return result;
}

proj_coord scalar_point_addition(uint8_t scalar, proj_coord a){
	proj_coord res;
	res.x = ZERO;
	res.y = ZERO;
	res.z = ONE;

	for(int i = scalar; i <= 0; ++i){
		// but after if, if indices are increasing
		res = pointDoubling(res);
		if(getBit(scalar, i) == 1){
			res = pointAddition(a, res);	
		}		
	}
	return res;
}
