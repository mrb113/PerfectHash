#include "test.h"

void main() {
	int length = 3; 
	uint input[3] = { 1, 3, 4 };
	
	lookup lookuptable = CreateEmptyLookupTable(length);
	if (lookuptable.tablesize == -1) {
		printf("Lookup table creation failed\n");
	}
	printf("Original hash: key: 1. Hash: %d. key 3. Hash: %d. key 4. Hash: %d\n", Hash(1, 0) & (lookuptable.tablesize - 1), Hash(3, 0) & (lookuptable.tablesize - 1), Hash(4, 0) & (lookuptable.tablesize - 1)); 
	printf("with 1 hash: key: 1. Hash: %d. key 3. Hash: %d. key 4. Hash: %d\n", Hash(1, 1) & (lookuptable.tablesize - 1), Hash(3, 1) & (lookuptable.tablesize - 1), Hash(4, 1) & (lookuptable.tablesize - 1));
	if (GeneratePerfectHash(input, lookuptable, length) == FAILURE){
		printf("Hash creation failed");
	}
	printlookuptable(&lookuptable, lookuptable.tablesize);
	getchar(); 
}

void printlookuptable(lookup* lookuptable, int size){
	for (int i = 0; i < size; i++) {
		printf("%d: %d\n", i, lookuptable->table[i]); 
	}
}

void printbucketlist(p_bucket bucketlist, int size) {
	for (int i = 0; i < size; i++) {	
		if (bucketlist[i].slot >= 0 && bucketlist[i].slot <= size)
		printbucket(&bucketlist[i]);
	}
}

void printbucket(p_bucket bucket){
	if (bucket->size == 0) {
		return; 
	}
	printf("Printing bucket %d contents. Size: %d\n", bucket->slot, bucket->size); 
	p_keynode k = bucket->head;
	
	while (k != NULL) {
		printf("Key: %d\n", k->key); 
		k = k->next; 
	}
}