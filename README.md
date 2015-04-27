# PerfectHash
####Perfect hash function generator for Windows in C

PerfectHash is a performant library to generate a perfect hash function (i.e. no collisions) for a set of keys. Optimized for lookup speed. 

NOTE: This library does not generate a minimum perfect hash function because MPHFs are not performance-friendly. However, since this library always generates a table size that is a power of two, it will work out to be an MPHF if your number of keys is also a power of two. If you don't know what a minimum perfect hash function is, then you're probably a-okay to go ahead with this one. 

####How To Use
0. Some (messy) tests are in test.c. The example generates a perfect hash function for the keys in kernellist.txt. NOTE: This wasn't designed to be a workable example and was for my own testing/performance measurement; in fact, I'd advise against using it right now. Making a better example is on my todo list.
1. Create an empty lookup table. This will store the perfect hash function for your keys.  Call CreateEmptyLookupTable(int length) where length = the number of keys. 
2. GeneratePerfectHash(uint* input, lookup lookuptable, int length) with your key array, newly created lookup table, and the number of keys (the same value you passed in to CreateEmptyLookupTable)
3. Create a hash table. Example: uint *hashtable = malloc(lookuptable.tablesize * sizeof(uint)); Remember to free this when you're done!
4. We have our hash function and our hash table, now we can insert keys into the table with our hash function. Insert(key, value, lookuptable, hashtable);
5. To look up values that we've previously inserted, we can Lookup(key, lookuptable, hashtable); to get the value
6. When you're all done, call FreeLookupTable(lookuptable); and free() your hash table array. 

#####Hash functions
Several different hash functions for integers are included in hashfunction.c. The number after the hash function is the number of shift operations it takes; i.e. Hash5() uses 5 shifts. The 5 and 6 shift hash functions may provide better results depending on your input. Since I am interested in the fewest number of operations possible for lookup, I use Hash4() and HashZeroInlined4() since it uses only 4 shifts and produces acceptable results for my keys. Feel free to swap out the hash functions in your own use. 

#####Definition of perfect hash function from Wikipedia: 
A perfect hash function for a set S is a hash function that maps distinct elements in S to a set of integers, with no collisions. A perfect hash function has many of the same applications as other hash functions, but with the advantage that no collision resolution has to be implemented. In mathematical terms, it is a total injective function.

#####How It Works: 
Algorithm: Use [CHD algorithm](http://cmph.sourceforge.net/chd.html) to generate a hash function for a set of integers. 
Hash function: Modify [Bob Jenkins' six-shift integer hash function](http://burtleburtle.net/bob/hash/integer.html) to take a seed. 

#####Future work: 
- Further optimize lookup by adding a bitmap to the lookup. This can give an extra shortcut - if the bit is 0, then we can use the zero inlined hash function and save ourselves from 6 shift operations. If the bit is 1, continue with lookup in the table. We especially benefit if there are mostly 0s in the table. 
- Consider compression on the lookup table/associated bitmap 
- Improve test.c to be a better example on how to use PerfectHash API. 
