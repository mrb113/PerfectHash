#include "test.h"


void main() {
	// Add tests here as needed
	
	kvp input[3] = { { 0, 132, NULL }, { 1, 300, NULL }, { 2, 800, NULL } };
	int lookup[4]; 
	kvp hash[4];
	memset(hash, 0xff, 4 * sizeof(int));
	printf("With seed 0:\n"); 
	for (int i = 0; i < 3; i++) {
		int test = Hash(input[i].key, 0) & 3;
		printf("Input: %d Hash: %d\n", input[i].key, test);
	}

	printf("With seed 1:\n");
	for (int i = 0; i < 3; i++) {
		int test = Hash(input[i].key, 1) & 3;
		printf("Input: %d Hash: %d\n", input[i].key, test);
	}
	PerfectHash(input, lookup, hash, 3);
	printf("Found something\n");
	printhashtable(hash, 4);
	printlookuptable(lookup, 4);
	getchar(); 
}

void printlookuptable(int* lookuptable, int size){
	for (int i = 0; i < size; i++) {
		printf("%d: %d\n", i, lookuptable[i]); 
	}
}

void printhashtable(p_kvp hashtable, int size){
	for (int i = 0; i < size; i++) {
		printf("%d| k: %d v: %u\n", i, hashtable[i].key, hashtable[i].value); 
	}
}

void printbucketlist(p_bucket bucketlist, int size) {
	for (int i = 0; i < size; i++) {	
		if (bucketlist[i].collisionvalue >= 0 && bucketlist[i].collisionvalue <= size)
		printbucket(&bucketlist[i]);
	}
}

void printbucket(p_bucket bucket){
	printf("Printing bucket %d contents. Size: %d\n", bucket->collisionvalue, bucket->size); 
	p_kvp k = bucket->keyvalue;
	while (k != NULL) {
		printf("Key: %d Value: %d\n", k->key, k->value); 
		k = k->next; 
	}
}