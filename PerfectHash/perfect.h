#include <stdlib.h>
#include <stdio.h>



/* Largest signed integer power of 2 */
#define MAX_INPUT 2^30

typedef unsigned int uint;

uint hash(uint a, uint seed);

int nextPowerOfTwo(int v);
uint lookup(uint key, int* lookuptable, int* values);
