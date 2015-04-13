#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;

/* Macro for number of elements in an array */
#define length(array) (sizeof(array)/sizeof(*(array)))

/* 2^30: Largest signed integer power of 2 */
#define MAX_INPUT 1073741824

/* Key/value pair */
typedef struct KEY_VALUE_PAIR {
	uint key; 
	uint value; 
} kvp, *p_kvp;

uint hash(uint a, uint seed);
int nextPowerOfTwo(int v);
uint lookup(uint key, int* lookuptable, p_kvp hashtable); 
