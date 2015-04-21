#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned int uint;
typedef unsigned char uchar; 

/* Macro for number of elements in an array */
#define length(array) (sizeof(array)/sizeof(*(array)))

/* 2^30: Largest signed integer power of 2 */
#define MAX_INPUT 1073741824

// TODO magic number
#define MAX_TRIES 100000

/* Exit codes */
#define FAILURE 0
#define SUCCESS 1

/* Key node */
typedef struct KEY_NODE {
	uint key; 
	struct KEY_NODE *next; 
} keynode, *p_keynode;

/* Bucket contains list of keys that collide with original hash function */
typedef struct BUCKET {
	p_keynode head; 
	int slot; 
	int size; 
} bucket, *p_bucket;

typedef struct LOOKUP_TABLE {
	uchar* table; 
	int tablesize; 
} lookup, *p_lookup;

uint Hash(uint a, uint seed);

int GeneratePerfectHash(uint* input, lookup lookuptable, int length);
int FindSeed(p_bucket b, char* collisions, int tablesize);
int VerifyNoBucketCollisions(p_bucket b, int tablesize, char* collisions, int seed);
int VerifyNoHashTableCollisions(p_bucket b, char* collisiontable, int tablesize, int seed);
int AddNodeToBucket(p_bucket b, uint key);
uint Lookup(uint key, lookup lookuptable, uint* hashtable);
void Insert(uint key, uint value, lookup lookuptable, uint* hashtable);
int NextPowerOfTwo(int v);
int BucketCompare(const void* a, const void* b);
void FreeKeys(p_keynode head);
lookup CreateEmptyLookupTable(int length); 
void FreeLookupTable(lookup lookuptable);
void UndoCollisionTableAdd(p_keynode head, p_keynode final, char* collisions, int seed, int tablesize);