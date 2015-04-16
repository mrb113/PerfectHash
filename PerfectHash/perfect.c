//#include "perfect.h"
#include "test.h"
/* Generate a perfect hash function */
int perfectHash(p_kvp input, int* lookuptable, int* hashtable, int length) {
	
	// If we input too many keys, fail
	if (length > MAX_INPUT) {
		return 0;
	}

	const int tablesize = nextPowerOfTwo(length); 
	
	// Create array of buckets
	bucket* buckets = malloc(tablesize * sizeof(bucket));
	if (buckets == NULL) {
		free(buckets);
		return 0;
	}

	bucket empty; 
	empty.keyvalue = NULL; 
	for (int i = 0; i < tablesize; i++){
		buckets[i] = empty; 
	}

	// Create buckets by regular hashing
	for (int i = 0; i < length; i++) {

		int slot = (int)hash(input[i].key, 0) & (tablesize - 1);
		buckets[slot].collisionvalue = slot; 

		// Add the key/value pair to the correct bucket
		if (addNodeToBucket(&buckets[slot], input[i].key, input[i].value) == 0) {
			return 0; 
		}		
	} 
	printf(" Printing bucket list:\n"); 
	printbucketlist(buckets, tablesize);
	// TODO 2. sort buckets
	// TODO 3. for each bucket, find a seed that works for no collisions
	// TODO 4. When found, add the values into the hash table
	// TODO 5. insert seed into lookuptable[(int)hash(bucket[0].key, 0) & (length(lookuptable) - 1)]; 

	return 1; 
}

/* Adds a key/value pair node to the beginning of the bucket */
int addNodeToBucket(p_bucket b, uint key, uint value) {
	
	p_kvp head = b->keyvalue; 
    p_kvp new_head = (p_kvp) malloc (sizeof (kvp));

	if (new_head == NULL) {
		return 0; 
	}
    new_head->key = key;
	new_head->value = value; 
    new_head->next = head;

	b->keyvalue = new_head; 
	// Increase bucket size
	b->size++; 
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