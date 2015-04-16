#include "test.h"


void main() {
	// Add tests here as needed

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