#include "test.h"
void main() {
    // Michelle's hacky "test as you go" setup
    // No real test framework yet

    struct timeb start, end;
    int diff;

    uint kernelbasekeys[36954];
    FILE *pKernelList;
    if (fopen_s(&pKernelList, "C:\\Users\\Michelle\\Documents\\PerfectHash\\kernelbase.txt", "r") != 0) {
        printf("file read failed\n");
        return;
    }
    for (int i = 0; i < 36954; i++){
        uint number;
        fscanf_s(pKernelList, "%x", &number);
        kernelbasekeys[i] = 63580000 - number;
        if (feof(pKernelList)){
            break;
        }
    }

    // Round up the current # of keys for link /dump /headers /loadconfig mshtml.dll (~37000)
    int length = 36954;
    printf("Number of keys: %d\n", length);
    uint values[36954];
    for (int i = 0; i < length; i++) {

        values[i] = i;
    }

    lookup lookuptable = CreateEmptyLookupTable(length);
    assert(lookuptable.tablesize != -1);

    ftime(&start);
    assert(GeneratePerfectHash(kernelbasekeys, lookuptable, length) != FAILURE);
    ftime(&end);

    diff = (int)(1000.0 * (end.time - start.time)+ (end.millitm - start.millitm));
    printf("Time taken in milliseconds to generate perfect hash function: %u\n\n", diff);
    printf("Inserting keys into hash table where input[i]'s key = i...\n");
    uint *hashtable = malloc(lookuptable.tablesize * sizeof(uint));
    for (int i = 0; i < length; i++) {
        Insert(kernelbasekeys[i], values[i], lookuptable, hashtable);
    }
    printf("Done inserting.\n\n");
    printf("Looking up value of key input[30]: \n");
    int key = kernelbasekeys[30];
    int val = Lookup(key, lookuptable, hashtable);
    printf("Found value %d\n", val);
    printf("Timing lookup of every key:\n");
    ftime(&start);
    for (int i = 0; i < length; i++) {
        Lookup(kernelbasekeys[i], lookuptable, hashtable);
    }
    ftime(&end);
    diff = (int)(1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
    printf("Time taken in milliseconds to lookup every key: %u\n\n", diff);

    // Values are all key+
    calculatePercentageEmpty(lookuptable);
    printf("Done.\n");
    FreeLookupTable(lookuptable);
    free(hashtable);
    getchar();
}

// Use keys from MSHTML.dll

// Use hash function 1
// Calculate percentage of 1s in lookup table

// Use hash function 2
// Calculate percentage of 1s in lookup table
void calculatePercentageEmpty(lookup lookuptable) {
    printf("Calculating the percentage of nonzero elements in lookup table of size: %d\n", lookuptable.tablesize);
    int count = 0;
    for (int i = 0; i < lookuptable.tablesize; i++) {
        if (lookuptable.table[i] > 0) {
            count++;
        }
    }
    double percentage = (double)count / (double)lookuptable.tablesize;
    printf("%f \n", percentage);
}

void printlookuptable(lookup* lookuptable, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d: %d\n", i, lookuptable->table[i]);
    }
}

void printbucketlist(p_bucket bucketlist, int size) {
    for (int i = 0; i < size; i++) {
        if (bucketlist[i].slot >= 0 && bucketlist[i].slot <= size)
        printbucket(&bucketlist[i]);
    }
}

void printbucket(p_bucket bucket) {
    if (bucket->size == 0) {
        return;
    }
    printf("Printing bucket %d contents. Size: %d\n", bucket->slot, bucket->size);
    p_keynode k = bucket->head;

    while (k != NULL) {
        printf("Key: %d\n", k->key);
        k = k->next;
    }
}