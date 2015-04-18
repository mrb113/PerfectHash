//#include "perfect.h"
#include "test.h"
/* Generate a perfect hash function */
int PerfectHash(p_kvp input, int* lookuptable, p_kvp hashtable, int length) {
	int exitCode = FAILURE; 

	// If we input too many keys, fail
	if (length > MAX_INPUT) {
		return exitCode; 
	}
	
	const int tablesize = NextPowerOfTwo(length); 
	
	// Fill hashtable with empty kvps
	kvp emptykvp;
	emptykvp.key = -1;
	for (int i = 0; i < tablesize; i++){
		hashtable[i] = emptykvp;
	}

	// Create array of buckets
	bucket* buckets = malloc(tablesize * sizeof(bucket));
	if (buckets == NULL) { 
		goto Cleanup; 
	}

	// Fill array with empty buckets
	bucket emptybucket; 
	emptybucket.keyvalue = NULL; 
	emptybucket.size = 0; 
	for (int i = 0; i < tablesize; i++){
		buckets[i] = emptybucket; 
	}

	// Create buckets by regular hashing
	for (int i = 0; i < length; i++) {

		int slot = (int)Hash(input[i].key, 0) & (tablesize - 1);
		buckets[slot].collisionvalue = slot; 

		// Add the key/value pair to the correct bucket
		if (AddNodeToBucket(&buckets[slot], input[i].key, input[i].value) == FAILURE) {
			goto Cleanup; 
		}		
	} 

	// Sort the buckets
	// NOTE: Implementing a version of radix sort may be more efficient than quick sort
	// For time, I'm leaving it at quick sort
	qsort(buckets, tablesize, sizeof(bucket), BucketCompare);
	
	// If the largest bucket is of size 1, we already have no collisions
	if (buckets[0].size == 1) {

		// Create lookup table and hash table
		memset(lookuptable, 0, tablesize * sizeof(int));
		for (int i = 0; i < length; i++) {
			int slot = (int)Hash(input[i].key, 0) & (tablesize - 1);
			hashtable[slot] = input[i];
		}

		exitCode = SUCCESS; 
		goto Cleanup; 
	}

	// For each bucket, find a seed that works for no collisions
	int seed; 
	p_kvp k; 
	for (int i = 0; i < tablesize; i++) {

		// If we only have empty buckets left, stop.
		if (buckets[i].size == 0) {
			break; 
		}
		seed = FindSeed(&buckets[i], hashtable, tablesize);
		if (seed == -1) {
			goto Cleanup;
		}
		// Add the seed to the lookup table 
		int lookupslot = buckets[i].collisionvalue;
		lookuptable[lookupslot] = seed;

		// Add the values to the hash table 
		k = buckets[i].keyvalue;
	
		while (k != NULL) {
			Insert(*k, seed, hashtable, tablesize);
			k = k->next;
		}
	}
	exitCode = SUCCESS;

Cleanup:
	if (buckets) {
		for (int i = 0; i < tablesize; i++) {
			FreeKeyValues(buckets[i].keyvalue);
		}
	}
	return exitCode; 
}

/* Find a new seed that works for all of the values in the bucket */
int FindSeed(p_bucket b, p_kvp hashtable, int tablesize) {

	p_kvp k = b->keyvalue;
	int seed = 1; 
	int lookupslot = Hash(k->key, 0) & (tablesize - 1);
	int hashslot, seedfound; 
	
	// Start looking for a seed
	while (1) {
		k = b->keyvalue;
		seedfound = -1; 		

		// If we have more than one kvp in a bucket, make sure they won't collide with each other.
		if (b->size > 1) {
			int* values = malloc(tablesize * sizeof(int));
			if (values == NULL) {
				return FAILURE; 
			}
			memset(values, 0xff, tablesize * sizeof(int));
			int i = 0; 
			
			// Check each value for collisions with others in the bucket
			while (k != NULL) {
				if (values[i] != -1) {
					seedfound = 0;
					seed++;
					break;
				}
				values[i] = Hash(k->key, seed) & (tablesize - 1);	
				
				k = k->next;
				i++; 
			}
			free(values);

			// Try the next seed if we are unsuccessful here
			if (seedfound == 0) {
				continue;
			}			

			k = b->keyvalue;
		}		
		// Check to see if our new seed generates collisions
		while (k != NULL) {
			hashslot = Hash(k->key, seed) & (tablesize - 1);
			if (hashtable[hashslot].key != -1) {
				seedfound = 0;
				seed++;
				break; 
			}
			k = k->next;
		}
		if (seedfound == 0) {
			continue; 
		}
		return seed; 
	}	
	return FAILURE; 
}

/* Adds a key/value pair node to the beginning of the bucket */
int AddNodeToBucket(p_bucket b, uint key, uint value) {
	
	p_kvp head = b->keyvalue;
    p_kvp new_head = (p_kvp) malloc (sizeof (kvp));
	
	if (new_head == NULL) {
		return FAILURE; 
	}
    new_head->key = key;
	new_head->value = value; 
    new_head->next = head;

	b->keyvalue = new_head; 
	// Increase bucket size
	b->size++; 
	return SUCCESS; 
}

/* Return a value in the hash table given a key */
uint Lookup(uint key, int* lookuptable, p_kvp hashtable) {
	
	// Grab the hash function seed from the lookup table	
	int lookupslot = (int)Hash(key, 0) & (length(lookuptable) - 1);
	int seed = lookuptable[lookupslot];

	// Get the actual value from the hash table
	int valueslot = (int)Hash(key, seed) & (length(hashtable) - 1);

	int value = hashtable[valueslot].value;
	return value; 	
}

/* Insert an item into the hash table using the seed */
void Insert(kvp toinsert, int seed, p_kvp hashtable, int tablesize) {
	int hashslot = Hash(toinsert.key, seed) & (tablesize - 1);
	hashtable[hashslot] = toinsert; 
}

/* Round up to the next power of 2 */
int NextPowerOfTwo(int v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v; 
}

/* For sorting: The bucket with the larger size wins */ 
int BucketCompare(const void* a, const void* b) {
	const bucket *elem1 = a;
	const bucket *elem2 = b;

	return elem2->size - elem1->size; 
}

void FreeKeyValues(p_kvp k) {
	p_kvp current = k; 
	p_kvp temp; 
	while (k != NULL) {
		temp = current; 
		free(temp); 
		current = current->next; 
	}
}