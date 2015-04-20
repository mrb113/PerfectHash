#include "test.h"

void main() {
	// Michelle's hacky "test as you go" setup
	// No real test framework yet

	struct timeb start, end;
	int diff;

	// Round up the current # of keys for link /dump /headers /loadconfig mshtml.dll (~37000)
	int length = 40000;
	uint input[40000];
	uint values[40000];
	for (int i = 0; i < length; i++) {
		input[i] = i; 
		values[i] = i+1; 
	}
	
	lookup lookuptable = CreateEmptyLookupTable(length);
	assert(lookuptable.tablesize != -1);

	ftime(&start);
	assert(GeneratePerfectHash(input, lookuptable, length) != FAILURE);
	ftime(&end);

	diff = (int)(1000.0 * (end.time - start.time)+ (end.millitm - start.millitm));
	printf("Time taken in milliseconds to generate perfect hash function: %u\n", diff);
	printf("Inserting keys into hash table\n");
	uint *hashtable = malloc(lookuptable.tablesize * sizeof(uint));
	for (int i = 0; i < length; i++) {
		Insert(input[i], values[i], lookuptable, hashtable);
	}
	printf("Looking up value at key 5090: \n");
	int key = input[5090]; 
	int val = Lookup(key, lookuptable, hashtable);
	printf("Found value %d\n", val);

	// Values are all key+1
	assert(val == key+1);
	FreeLookupTable(lookuptable);
	free(hashtable);
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