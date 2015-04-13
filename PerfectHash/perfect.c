#include "perfect.h"

/* Generate a perfect hash function */
int perfectHash(int* input, int size, int* lookup, int* hashtable) {
	// If we input too many keys, fail
	if (size > MAX_INPUT) {
		return 0; 
	}
	
	// TODO the good stuff 

	return 1; 
}

/* Insert a key/value pair into the hashtable */
int insert(uint key, uint value){
	kvp add = { key, value };
	// TODO 
	return 1; 
}

/* Return a value in the hash table given a key */
uint lookup(uint key, int* lookuptable, p_kvp hashtable) {
	
	// Grab the hash function seed from the lookup table	
	int lookupslot = (int)hash(key, 0) & (length(lookuptable) - 1);
	int seed = lookuptable[lookupslot];

	// Get the actual value from the hash table
	int valueslot = (int)hash(key, seed) & (length(hashtable) - 1);

	// TODO use key/value pair
	int value = hashtable[valueslot].value;
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