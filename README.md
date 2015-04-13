# PerfectHash
Perfect hash function generator in C

###Definition of perfect hash function from Wikipedia: 
A perfect hash function for a set S is a hash function that maps distinct elements in S to a set of integers, with no collisions. A perfect hash function has many of the same applications as other hash functions, but with the advantage that no collision resolution has to be implemented. In mathematical terms, it is a total injective function.

###My approach: 
Algorithm: Use [CHD algorithm](http://cmph.sourceforge.net/chd.html) to generate a hash function for a set of integers. 
Hash function: Modify [Bob Jenkins' six-shift integer hash function](http://burtleburtle.net/bob/hash/integer.html) to take a seed. 