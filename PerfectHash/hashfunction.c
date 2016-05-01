#include "perfect.h"

/* Bob Jenkins' hash function modified to take a seed
   http://burtleburtle.net/bob/hash/integer.html */
uint Hash6(uint a, uint seed) {
    a = (a + seed) + (a << 12);
    a = (a ^ 0xc761c23c) ^ (a >> 19);
    a = (a + 0x165667b1) + (a << 5);
    a = (a + 0xd3a2646c) ^ (a << 9);
    a = (a + 0xfd7046c5) + (a << 3);
    a = (a ^ 0xb55a4f09) ^ (a >> 16);
    return a;
}

/* HashZeroInline
Description:
    We'll be using seed 0 most of the time, so we inline it */
uint HashZeroInline6(uint a) {
    a = (a) + (a << 12);
    a = (a ^ 0xc761c23c) ^ (a >> 19);
    a = (a + 0x165667b1) + (a << 5);
    a = (a + 0xd3a2646c) ^ (a << 9);
    a = (a + 0xfd7046c5) + (a << 3);
    a = (a ^ 0xb55a4f09) ^ (a >> 16);
    return a;
}

/* 5 shift hash function - zero inlined*/
uint HashZeroInline5(uint a) {
    a = (a)+(a << 8);
    a = (a ^ 0xe4aa10ce) ^ (a >> 5);
    a = (a + 0x9942f0a6) - (a << 14);
    a = (a ^ 0x5aedd67d) ^ (a >> 3);
    a = (a + 0x17bea992) + (a << 7);
    return a;
}

/* 5 shift hash function */
uint Hash5(uint a, uint seed) {
    a = (a + seed) + (a << 8);
    a = (a ^ 0xe4aa10ce) ^ (a >> 5);
    a = (a + 0x9942f0a6) - (a << 14);
    a = (a ^ 0x5aedd67d) ^ (a >> 3);
    a = (a + 0x17bea992) + (a << 7);
    return a;
}

/* 4 shift hash function - zero inlined */
uint HashZeroInline4(uint a) {
    a = (a ^ 0) + (a << 4);
    a = a ^ (a >> 10);
    a = a + (a << 7);
    a = a ^ (a >> 13);
    return a;
}

/* 4 shift hash function */
uint Hash4(uint a, uint seed) {
    a = (a ^ seed) + (a << 4);
    a = a ^ (a >> 10);
    a = a + (a << 7);
    a = a ^ (a >> 13);
    return a;
}

/* 3 shift hash function - zero inlined */
uint HashZeroInline3(uint a) {
    a = a ^ (a >> 4);
    a = (a ^ 0) + (a << 5);
    a = a ^ (a >> 11);
    return a;
}

/* 3 shift function */
uint Hash3(uint a, uint seed) {
    a = a ^ (a >> 4);
    a = (a ^ seed) + (a << 5);
    a = a ^ (a >> 11);
    return a;
}
