#include "test.h"


void main() {
	// Add tests here as needed

	kvp k = { 0, 132, NULL };
	kvp l = { 1, 300, NULL };

	kvp input[2] = { { 0, 132, NULL }, { 1, 300, NULL } };

	int lookuptable[4] = { 0, 1, 2, 3 };
	int hashtable[4] = { 0, 0, 0, 0 };

	perfectHash(input, lookuptable, hashtable, length(input));
	getchar(); 
}

void printlookuptable(int* hashtable){
	// TODO 
}

void printhashtable(p_kvp hashtable){
	// TODO 
}

void printbucketlist(p_bucket bucketlist) {
	for (int i = 0; i < length(bucketlist); i++) {		
		printbucket(&bucketlist[i]);
	}
}

void printbucket(p_bucket bucket){
	printf("Printing bucket contents: \n"); 
	p_kvp k = bucket->keyvalue;
	while (k != NULL) {
		printf("Key: %d Value: %d\n", k->key, k->value); 
		k = k->next; 
	}
}