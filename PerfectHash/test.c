#include "test.h"

void main() {
	
}

void printlookuptable(int* lookuptable, int size){
	for (int i = 0; i < size; i++) {
		printf("%d: %d\n", i, lookuptable[i]); 
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
	p_keynode k = bucket->head;
	while (k != NULL) {
		printf("Key: %d\n", k->key); 
		k = k->next; 
	}
}