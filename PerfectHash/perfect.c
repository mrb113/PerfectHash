//#include "perfect.h"
#include "test.h"
/* Generate a perfect hash function */
int GeneratePerfectHash(uint* input, int* lookuptable, int length) {
	int exitCode = FAILURE; 

	// If we input too many keys, fail
	if (length > MAX_INPUT) {
		return FAILURE; 
	}
	
	const int tablesize = NextPowerOfTwo(length); 

	// Create array of buckets
	bucket* buckets = malloc(tablesize * sizeof(bucket));
	if (buckets == NULL) { 
		goto Cleanup; 
	}

	// Fill array with empty buckets
	bucket emptybucket; 
	emptybucket.head = NULL; 
	emptybucket.size = 0; 
	for (int i = 0; i < tablesize; i++){
		buckets[i] = emptybucket; 
	}

	// Create buckets by regular hashing
	for (int i = 0; i < length; i++) {
		int slot = (int)Hash(input[i], 0) & (tablesize - 1);
		buckets[slot].collisionvalue = slot; 

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
		memset(lookuptable, 0, tablesize * sizeof(int));
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
		seed = FindSeed(&buckets[i], tablesize);
		if (seed == FAILURE) {
			goto Cleanup;
		}
		// Add the seed to the lookup table 
		int lookupslot = buckets[i].collisionvalue;
		lookuptable[lookupslot] = seed;
	}
	exitCode = SUCCESS;

Cleanup:
	if (buckets) {
		for (int i = 0; i < tablesize; i++) {
			FreeKeys(buckets[i].head);
		}
	}
	return exitCode; 
}

/* Find a new seed that works for all of the values in the bucket */
int FindSeed(p_bucket b, int tablesize) {
	char* collisions = malloc(tablesize * sizeof(char));
	memset(collisions, 0xff, tablesize * sizeof(int));

	p_keynode key = b->head;
	int seed = 1; 
	
	// Start looking for a seed
	while (1) {
		key = b->head;	

		// If we have more than one key in a bucket, make sure they won't collide with each other.
		if (b->size > 1 && VerifyNoBucketCollisions(b, tablesize, seed) == FAILURE) {
			seed++; 
			continue; 
		}		

		// Check to see if our new seed generates collisions with values in the existing hash table		
		if (VerifyNoHashTableCollisions(b, collisions, tablesize, seed) == FAILURE) {
			seed++; 
			continue; 
		}
		free(collisions);
		return seed; 
	}	
	free(collisions); 
	return FAILURE; 
}

/* When testing a new seed, check that it won't cause collisions between any keys in the bucket */
int VerifyNoBucketCollisions(p_bucket b, int tablesize, int seed) {
	int exitCode = FAILURE; 

	char* values = malloc(tablesize * sizeof(char));
	if (values == NULL) {
		return exitCode;
	}

	// Fill values[] with -1: 
	memset(values, 0xff, tablesize * sizeof(char));

	int slot;
	p_keynode k = b->head; 

	// Check each value for collisions with others in the bucket
	while (k != NULL) {
		slot = Hash(k->key, seed) & (tablesize - 1);
		if (values[slot] != -1) {
			goto Cleanup; 
		}
		// Mark the spot as full
		values[slot] = 1; 
		k = k->next;
	}
	exitCode = SUCCESS; 

Cleanup: 
	if (values) {
		free(values);
	}	

	return exitCode; 
}

int VerifyNoHashTableCollisions(p_bucket b, char* collisiontable, int tablesize, int seed) {
	p_keynode k = b->head; 
	int hashslot; 
	while (k != NULL) {
		hashslot = Hash(k->key, seed) & (tablesize - 1);
		if (collisiontable[hashslot] != -1) {
			return FAILURE; 
		}
		k = k->next;
	}
	return SUCCESS; 
}

/* Adds a key pair node to the beginning of the bucket */
int AddNodeToBucket(p_bucket b, uint key) {
	
	p_keynode head = b->head;
    p_keynode new_head = (p_keynode) malloc (sizeof (key));
	
	if (new_head == NULL) {
		return FAILURE; 
	}
    new_head->key = key;
    new_head->next = head;

	b->head = new_head; 
	// Increase bucket size
	b->size++; 
	return SUCCESS; 
}

/* Return a value in the hash table given a key */
uint Lookup(uint key, int* lookuptable, uint* hashtable, int tablesize) {
	
	// Grab the hash function seed from the lookup table	
	int lookupslot = (int)Hash(key, 0) & (tablesize - 1);
	int seed = lookuptable[lookupslot];

	// Get the actual value from the hash table
	int valueslot = (int)Hash(key, seed) & (tablesize - 1);

	int value = hashtable[valueslot];
	return value; 	
}

/* Insert an item into the hash table using the seed */
void Insert(uint key, uint value, int seed, uint* hashtable, int tablesize) {
	int hashslot = Hash(key, seed) & (tablesize - 1);
	hashtable[hashslot] = value; 
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

void FreeKeys(p_keynode head) {
	p_keynode current = head; 
	p_keynode temp; 
	while (current != NULL) {
		temp = current; 
		current = current->next;
		free(temp); 
	}
	head = NULL; 
}