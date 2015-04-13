#include "perfect.h"

/* Test input */
int keys[4] = { 6, 23, 500 };
#define TABLE_SIZE nextPowerOfTwo(sizeof(keys) / sizeof(int))

/* Generate a perfect hash function */
int perfectHash(int* input, int size, int* lookup, int* values){

	
	// TODO the good stuff 

	return 1; 
}

/* Lookup a value in the hash table given a key */
uint lookup(uint key, int* lookuptable, int* values) {
	
	// Grab the hash function seed from the lookup table	
	int lookupslot = (int)hash(key, 0) & (TABLE_SIZE - 1);
	int seed = lookuptable[lookupslot];

	// Get the actual value from the hash table now
	int valueslot = (int)hash(key, seed) & (TABLE_SIZE - 1);
	uint value = values[valueslot];
	return value; 	
}

/* Round up to the next power of 2 */
int nextPowerOfTwo(int v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v; 
}