#include "hashfunction.h"
uint32_t hashint(uint32_t a, uint32_t seed)
{
	a = (a ^ seed) + (a << 4);
	a = a ^ (a >> 10);
	a = a + (a << 7);
	a = a ^ (a >> 13);
	return a;
}

uint32_t hash(uint32_t a, uint32_t seed)
{
	a = (a + seed) + (a << 12);
	a = (a ^ 0xc761c23c) ^ (a >> 19);
	a = (a + 0x165667b1) + (a << 5);
	a = (a + 0xd3a2646c) ^ (a << 9);
	a = (a + 0xfd7046c5) + (a << 3);
	a = (a ^ 0xb55a4f09) ^ (a >> 16);
	return a;
}