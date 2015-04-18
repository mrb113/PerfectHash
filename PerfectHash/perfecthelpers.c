#include "perfect.h"

/* FindSeed
Description:
Find a new seed that works for all of the values in the bucket
Parameters:
b: Pointer to the bucket for which we are finding a seed that generates no collisions
collisiontable: Table storing which slots in the hash table are taken
tablesize: Number of elements in the hash table
Returns:
0 on failure, 1 on success
*/
int FindSeed(p_bucket b, char* collisions, int tablesize) {

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

/* VerifyNoBucketCollisions
Description:
When testing a new seed, check that it won't cause collisions between any keys in the bucket.
Parameters:
b: Pointer to the bucket for which we are testing a new seed value
tablesize: The number of elements in the hash table
seed: The seed to test
Returns:
0 on failure, 1 on success
*/
int VerifyNoBucketCollisions(p_bucket b, int tablesize, int seed) {
	int exitCode = FAILURE;

	// Create a temporary table to check the bucket values
	char* values = malloc(tablesize * sizeof(char));
	if (values == NULL) {
		return FAILURE;
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

/* VerifyNoHashTableCollisions
Description:
When testing a new seed, check that it won't cause collisions between any keys in the bucket.
Parameters:
b: Pointer to the bucket for which we are testing a new seed value
collisiontable: Represents
tablesize: The number of elements in the hash table
seed: The seed to test
Returns:
0 on failure, 1 on success
*/
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

/* AddNodeToBucket
Description:
Adds a key pair node to the beginning of the bucket
Parameters:
b: Pointer to the bucket to add
key: Key to add to the bucket
Returns:
0 on failure, 1 on success
*/
int AddNodeToBucket(p_bucket b, uint key) {

	p_keynode head = b->head;
	p_keynode new_head = (p_keynode)malloc(sizeof(key));

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

/* NextPowerOfTwo
Description:
Round an integer up to the next power of 2
Parameters:
v: The integer to round up
Returns:
The rounded-up value of the integer
*/
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

/* BucketCompare
Description:
For sorting: The bucket with the larger size wins
Parameters:
a, b: Buckets whose size we want to compare
Returns:
Value indicating the larger of the buckets - to pass to the sort method
*/
int BucketCompare(const void* a, const void* b) {
	const bucket *elem1 = a;
	const bucket *elem2 = b;

	return elem2->size - elem1->size;
}

/* FreeKeys
Description:
Frees a linked list of keys
Parameters:
head: The head of the linked list of keys to free
*/
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