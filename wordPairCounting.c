/*
Assignment 1
9/5/2023
CS 360
Elijah Delavar

Files:
    main.c hash.c hash.h wordPairCounting.c wordPairCounting.h getWord.c getWord.h crc.c crc.h README.md Makefile
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "wordPairCounting.h"
#include "getWord.h"

kv *newEntry(char *key) {
    assert(key);

    // Init entry
    kv *entry = NULL;
    while (!entry) entry = (kv*)malloc(sizeof(kv));

    entry->key = NULL;
    entry->val = NULL;
    entry->next = NULL;

    // Key
    while (!entry->key) entry->key = (char*)malloc(sizeof(char)*strlen(key)+1);
    strcpy(entry->key, key);

    // Occurance
    occ *count = NULL;
    while (!count) count = (occ*)malloc(sizeof(occ));
    count->x = 1;
    entry->val = count;

    return entry;
}

void readWordPairs(table *ht, FILE *fd) {
    assert(ht);
    assert(fd);

    char *w1 = getNextWord(fd);
    char *w2 = getNextWord(fd);
    if (!w2) {
        return;
    }

    // Key used for concatenating the two words together.
    char *key = NULL;
    size_t keyLen = strlen(w1) + strlen(w2) + 2;
    while (!key) key = (char*)malloc(sizeof(char)*keyLen);

    while (w2) {
        size_t len1 = strlen(w1);
        size_t len2 = strlen(w2);

        if (len1 + len2 + 2 > keyLen) {
            // resize key
            keyLen = len1 + len2 + 2;
            char *temp = NULL;
            while (!temp) temp = (char*)realloc(key, sizeof(char)*keyLen);
            key = temp;
        }

        // Join word 1 to word 2 with a space in between
        strcpy(key, w1);
        strcat(key, " ");
        strcat(key, w2);

        // Find if key exists already in hash table
        occ *existingVal = (occ*)find(ht, key);
        if (existingVal) {
            // Increase occurance
            existingVal->x += 1;
        } else {
            // Insert new entry
            insert(ht, newEntry(key));
        }
        
        // free w1 since it is malloc'd memory
        free(w1);

        // word pairs are subsequent, so the second word becomes the first word
        w1 = w2;
        w2 = getNextWord(fd);
    }

    free(key);

    if (w1){
        free(w1);
    }
}

void readFile(table *ht, const char *fn) {
    assert(ht);
    assert(fn);

    FILE *fd = fopen(fn, "r");
    if (!fd) {
        fprintf(stderr, "Could not open file with file name <%s>\n", fn);
        exit(1);
    }

    readWordPairs(ht, fd);

    fclose(fd);
}

int compar(const void *p1, const void *p2) {
    assert(p1);
    assert(p2);

    kv *e1 = (kv*)p1;
    kv *e2 = (kv*)p2;

    if (((occ*)(e1->val))->x > ((occ*)(e2->val))->x) {
        return -1;
    }
    if (((occ*)(e1->val))->x < ((occ*)(e2->val))->x) {
        return 1;
    }
    return 0;
}

/*
Convert the hash table <ht> to an array sorted in decreasing order of occurance.

@return sorted array
*/
kv* convertHashTableToSortedArray(table *ht) {
    assert(ht);

    kv *arr = NULL;
    while (!arr) arr = (kv*)malloc(sizeof(kv)*ht->numEntries);

    // copy ht entries into arr
    unsigned long jj = 0;
    for (unsigned long ii = 0; ii < ht->size; ii++) {
        kv *entry = ht->array[ii];

        while (entry) {
            arr[jj].key = entry->key;
            arr[jj++].val = entry->val;
            entry = entry->next;
        }
    }

    qsort(arr, ht->numEntries, sizeof(kv), compar);

    return arr;
}

void printWordPairs(table *ht, unsigned long size) {
    assert(ht);

    kv *arr = convertHashTableToSortedArray(ht);

    for (unsigned long ii = 0; ii < size; ii++) {
        kv entry = arr[ii];
        printf("%10ld %s\n", ((occ*)(entry.val))->x, entry.key);
    }

    free(arr);
}