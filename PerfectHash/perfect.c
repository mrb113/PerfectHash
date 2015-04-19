#include "perfect.h"

/* GeneratePerfectHash 
Description: 
	Generate a perfect hash function for a set of keys
Parameters: 
	input: The set of keys for which to generate a hash function
	lookuptable: Table in which to place the seed values for our perfect hash function
	length: The number of elements in the input
Returns: 
	0 on failure, 1 on success
*/
int GeneratePerfectHash(uint* input, lookup lookuptable, int length) {

	int exitCode = FAILURE; 
	// If we input too many keys, fail
	if (length > MAX_INPUT) {
		return FAILURE; 
	}
	
	const int tablesize = NextPowerOfTwo(length); 
	lookuptable.tablesize = tablesize; 

	// Create array of buckets and collision table
	bucket* buckets = calloc(tablesize, sizeof(bucket));
	char* collisions = calloc(tablesize, sizeof(char));
	if (buckets == NULL || collisions == NULL) { 
		goto Cleanup; 
	}

	// Create buckets by regular hashing
	for (int i = 0; i < length; i++) {
		int slot = (int)Hash(input[i], 0) & (tablesize - 1);
		buckets[slot].slot = slot; 

		// Add the key/value pair to the correct bucket
		if (AddNodeToBucket(&buckets[slot], input[i]) == FAILURE) {
			goto Cleanup; 
		}		
	} 

	// Sort the buckets
	// NOTE: Implementing a version of radix sort may be more efficient than quick sort
	// For time, I'm leaving it at quick sort
	qsort(buckets, tablesize, sizeof(bucket), BucketCompare);
	
	// If the largest bucket is of size 1, we already have no collisions
	if (buckets[0].size == 1) {
		// Create lookup table 
		memset(lookuptable.table, 0, tablesize * sizeof(int));
		exitCode = SUCCESS; 
		goto Cleanup; 
	}

	// For each bucket, find a seed that works for no collisions
	int seed;
	for (int i = 0; i < tablesize; i++) {

		// If we only have empty buckets left, stop.
		if (buckets[i].size == 0) {
			break; 
		}
		seed = FindSeed(&buckets[i], collisions, tablesize);
		if (seed == FAILURE) {
			goto Cleanup;
		}
		// Add the seed to the lookup table 
		int lookupslot = buckets[i].slot;
		lookuptable.table[lookupslot] = seed;
	}
	exitCode = SUCCESS;

Cleanup:
	if (buckets) {
		for (int i = 0; i < tablesize; i++) {
			FreeKeys(buckets[i].head);
		}
		free(buckets);
	}
	if (collisions) {
		free(collisions);
	}
	return exitCode; 
}

/* Lookup
Description: 
	Return a value in the hash table given a key
Parameters:
	key: Key whose value we are looking up in the hash table 
	lookuptable: Table containing
	hashtable: The hash table containing values
	tablesize: Number of elements in the hash table
Returns: 
	The value from the hash table
*/
uint Lookup(uint key, lookup lookuptable, uint* hashtable) {
	// Grab the hash function seed from the lookup table	
	int lookupslot = (int)Hash(key, 0) & (lookuptable.tablesize - 1);
	int seed = lookuptable.table[lookupslot];

	// Get the actual value from the hash table
	int valueslot = (int)Hash(key, seed) & (lookuptable.tablesize - 1);

	int value = hashtable[valueslot];
	return value; 	
}

/* Insert
Description: 
	Insert an item into the hash table using the given seed 	
Parameters: 
	key: Key whose associated value we want to insert
	value: Value to insert
	lookuptable: Lookup table for the perfect hash function
	hashtable: Table to insert values into 
*/
void Insert(uint key, uint value, lookup lookuptable, uint* hashtable) {
	int lookupslot = Hash(key, 0) & (lookuptable.tablesize - 1);
	int seed = lookuptable.table[lookupslot];
	int hashslot = Hash(key, seed) & (lookuptable.tablesize - 1);
	hashtable[hashslot] = value; 
}