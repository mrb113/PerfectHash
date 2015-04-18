#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned int uint;

/* Macro for number of elements in an array */
#define length(array) (sizeof(array)/sizeof(*(array)))

/* 2^30: Largest signed integer power of 2 */
#define MAX_INPUT 1073741824

/* Exit codes */
#define FAILURE 0
#define SUCCESS 1

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

int PerfectHash(p_kvp input, int* lookuptable, p_kvp hashtable, int length);
int VerifyNoBucketCollisions(p_bucket b, int tablesize, int seed);
int VerifyNoHashTableCollisions(p_bucket b, p_kvp hashtable, int tablesize, int seed);
uint Hash(uint a, uint seed);
int NextPowerOfTwo(int v);
uint Lookup(uint key, int* lookuptable, p_kvp hashtable, int tablesize); 
int AddNodeToBucket(p_bucket b, uint key, uint value);
int BucketCompare(const void* a, const void* b); 
int FindSeed(p_bucket b, p_kvp hashtable, int tablesize);
void Insert(kvp toinsert, int seed, p_kvp hashtable, int tablesize);
void FreeKeyValues(p_kvp k);