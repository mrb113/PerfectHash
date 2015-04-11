#include <time.h>
#include "lookup3.h"
#include "murmur.h"
void main(){
	printf_s("Hello");
	uint32_t key = 308;
	uint32_t seed = 1;
	uint32_t  out = 0;
	clock_t start1, end1, start2, end2;
	double mcpu_time_used, lcpu_time_used;

	start1 = clock();
	for (uint32_t key = 0; key < 10000000; key++){
		MurmurHash3_x86_32(&key, sizeof(int), seed, &out);
	}
	end1 = clock();
	mcpu_time_used = ((double)(end1 - start1)) / CLOCKS_PER_SEC;

	printf_s("Murmur: Time: %f\n", mcpu_time_used);

	start2 = clock();
	for (uint32_t key = 0; key < 10000000; key++){
		lookup3_test(&key, sizeof(int), seed, &out);
	}
	end2 = clock();
	lcpu_time_used = ((double)(end2 - start2)) / CLOCKS_PER_SEC;
	printf_s("Lookup3: Time: %f\n", lcpu_time_used);
	printf_s("Lookup3 - Murmur: %f\n", lcpu_time_used - mcpu_time_used);
	getchar();

}