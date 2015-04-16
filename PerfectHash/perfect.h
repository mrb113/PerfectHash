#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned int uint;

/* Macro for number of elements in an array */
#define length(array) (sizeof(array)/sizeof(*(array)))

/* 2^30: Largest signed integer power of 2 */
#define MAX_INPUT 1073741824

/* Key/value pair node*/
typedef struct KEY_VALUE_PAIR {
	uint key; 
	uint value;
	struct KEY_VALUE_PAIR *next; 
} kvp, *p_kvp;

/* Bucket contains list of key/value pairs that collide with original hash function */
typedef struct BUCKET {
	p_kvp keyvalue; 
	int collisionvalue; 
	int size; 
} bucket, *p_bucket;

int perfectHash(p_kvp input, int* lookuptable, int* hashtable, int length);
uint hash(uint a, uint seed);
int nextPowerOfTwo(int v);
uint lookup(uint key, int* lookuptable, p_kvp hashtable); 
int addNodeToBucket(p_bucket b, uint key, uint value);
int bucketCompare(const void* a, const void* b); 
int FindSeed(bucket b, int* hashtable, int tablesize);