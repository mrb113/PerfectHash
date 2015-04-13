#include "perfect.h"

/* Generate a perfect hash function */
int perfectHash(kvp* input, int* lookuptable, int* hashtable) {

	// If we input too many keys, fail
	if (length(input) > MAX_INPUT) {
		return 0;
	}

	int tablesize = nextPowerOfTwo(length(input)); 

	
	// TODO 1. create buckets by regular hashing
	for (int i = 0; i < length(input); i++) {
		int slot = (int)hash(input[i].key, 0) & (tablesize - 1);
		// add input[i]
	}
	
	// TODO 2. sort buckets
	// TODO 3. for each bucket, find a seed that works for no collisions
	// TODO 4. When found, add the values into the hash table
	// TODO 5. insert seed into lookuptable[(int)hash(bucket[0].key, 0) & (length(lookuptable) - 1)]; 

	return 1; 
}

/* Return a value in the hash table given a key */
uint lookup(uint key, int* lookuptable, p_kvp hashtable) {
	
	// Grab the hash function seed from the lookup table	
	int lookupslot = (int)hash(key, 0) & (length(lookuptable) - 1);
	int seed = lookuptable[lookupslot];

	// Get the actual value from the hash table
	int valueslot = (int)hash(key, seed) & (length(hashtable) - 1);

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