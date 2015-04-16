#include "test.h"


void main() {
	// Add tests here as needed

	kvp k = { 0, 132, NULL };
	kvp l = { 1, 300, NULL };

	
	kvp input[3] = { { 0, 132, NULL }, { 1, 300, NULL }, { 6, 800, NULL } };
	int lookup[2] = { 1, 2 };
	int hash[2] = { 3, 6 };
	perfectHash(input, lookup, hash, 3);
	
	getchar(); 
}

void printlookuptable(int* hashtable){
	// TODO 
}

void printhashtable(p_kvp hashtable){
	// TODO 
}

void printbucketlist(p_bucket bucketlist, int size) {
	for (int i = 0; i < size; i++) {	
		if (bucketlist[i].collisionvalue >= 0 && bucketlist[i].collisionvalue <= size)
		printbucket(&bucketlist[i]);
	}
}

void printbucket(p_bucket bucket){
	printf("Printing bucket %d contents: \n", bucket->collisionvalue); 
	p_kvp k = bucket->keyvalue;
	while (k != NULL) {
		printf("Key: %d Value: %d\n", k->key, k->value); 
		k = k->next; 
	}
}
