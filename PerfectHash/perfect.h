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

/* Key node*/
typedef struct KEY_NODE {
	uint key; 
	struct KEY_NODE *next; 
} keynode, *p_keynode;

/* Bucket contains list of keys that collide with original hash function */
typedef struct BUCKET {
	p_keynode head; 
	int collisionvalue; 
	int size; 
} bucket, *p_bucket;

uint Hash(uint a, uint seed);

int GeneratePerfectHash(uint* input, int* lookuptable, int length);
int FindSeed(p_bucket b, char* collisions, int tablesize);
int VerifyNoBucketCollisions(p_bucket b, int tablesize, int seed);
int VerifyNoHashTableCollisions(p_bucket b, char* collisiontable, int tablesize, int seed);
int AddNodeToBucket(p_bucket b, uint key);
uint Lookup(uint key, int* lookuptable, uint* hashtable, int tablesize);
void Insert(uint key, uint value, int seed, uint* hashtable, int tablesize);
int NextPowerOfTwo(int v);
int BucketCompare(const void* a, const void* b);
void FreeKeys(p_keynode head);