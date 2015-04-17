#include "perfect.h"

/* Bob Jenkins' hash function modified to take a seed 
   http://burtleburtle.net/bob/hash/integer.html */ 
uint Hash(uint a, uint seed)
{
	a = (a + seed) + (a << 12);
	a = (a ^ 0xc761c23c) ^ (a >> 19);
	a = (a + 0x165667b1) + (a << 5);
	a = (a + 0xd3a2646c) ^ (a << 9);
	a = (a + 0xfd7046c5) + (a << 3);
	a = (a ^ 0xb55a4f09) ^ (a >> 16);
	return a;
}