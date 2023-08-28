/*
Assignment 1
9/5/2023
CS 360
Elijah Delavar

Files: TODO

Description: TODO
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "wordPairCounting.h"
#include "getWord.h"

kv *newEntry(char *key) {
    // Init entry
    kv *entry = NULL;
    while (!entry) entry = (kv*)malloc(sizeof(kv));

    entry->key = NULL;
    entry->val = NULL;
    entry->next = NULL;

    // Key
    entry->key = key;

    // Occurance
    occ *count = NULL;
    while (!count) count = (occ*)malloc(sizeof(occ));
    count->x = 1;
    entry->val = count;

    return entry;
}

void readWordPairs(table *ht, FILE *fd) {
    char *w1 = getNextWord(fd);
    char *w2 = getNextWord(fd);

    while (w2) {
        char *key = NULL;
        while (!key) key = (char*)malloc(sizeof(char)*(strlen(w1) + strlen(w2) + 2));

        // Join word 1 to word 2 with a space in between
        strcpy(key, w1);
        strcat(key, " ");
        strcat(key, w2);

        // Find if key exists already in hash table
        occ *existingVal = (occ*)find(ht, key);
        if (existingVal) {
            // Increase occurance
            existingVal->x += 1;
            free(key);
        } else {
            // Insert new entry
            insert(ht, newEntry(key));
        }
        free(w1); // free w1 since it is malloc'd memory
        w1 = w2;
        w2 = getNextWord(fd);
    }

    if (w1){
        free(w1);
    }
}

void readFile(table *ht, char *fn) {
    assert(fn);

    FILE *fd = fopen(fn, "r");
    assert(fd);

    readWordPairs(ht, fd);

    fclose(fd);
}

int compar(const void *p1, const void *p2) {
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

kv* convertHashTableToSortedArray(table *ht) {
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

void printWordPairs(kv *arr, unsigned long size) {
    for (unsigned long ii = 0; ii < size; ii++) {
        kv entry = arr[ii];
        printf("%10ld %s\n", ((occ*)(entry.val))->x, entry.key);
    }
}