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
#include <time.h>
#include "crc64.h" // Contains hash code function
#include "hash.h"

table* initTable(unsigned long size, table *ht) {
    if (!ht) {
        while (!ht) ht = (table*)malloc(sizeof(table));
    }

    ht->array = NULL;
    ht->numCollisions = 0;
    ht->numEntries = 0;
    ht->growing = 0;

    if (size == 0) {
        ht->size = 256;
    } else {
        ht->size = size;
    }

    while (!ht->array) ht->array = (kv**)calloc(ht->size, sizeof(kv*));

    return ht;
}

/*
Grow the hash table <ht> when the number of collisions per bucket is greater than 1.

I tested 2 ways of growing the array:
    average number of collisions across the buckets
    average number of collisions across the number of entries

In each test I ran the program with 10 Moby Dick files.
The first test ran for a rough average of 17 seconds.
The second test ran for a rough average of 19 seconds.

I tested 4 different thresholds:
    0.3
    1
    5
    50

A threshold of 1 performed best by roughly 1 second.
*/
void grow(table *ht) {
    assert(ht);

    float avgNumCollisions = (float)(ht->numCollisions / ht->size);

    if (avgNumCollisions > 1) {
        // grow array
        kv **oldArr = ht->array;
        unsigned long oldSize = ht->size;
        initTable(ht->size*3, ht); // reset hash table attributes and grow hash table array
        ht->growing = 1;

        for (unsigned long ii = 0; ii < oldSize; ii++) {
            kv *entry = oldArr[ii];

            while (entry) {
                kv *next = insert(ht, entry);
                entry = next;
            }
        }

        ht->growing = 0;

        free(oldArr);
    }
}

kv* insert(table *ht, kv *entry) {
    assert(ht);
    assert(entry);

    // save entry's next for easier growing
    kv *oldNext = entry->next;
    entry->next = NULL;

    // hash into ht
    unsigned long index = crc64(entry->key) % ht->size;

    // insert new entry at beginning of Linked List
    kv *existing = ht->array[index];
    
    if (existing) {
        entry->next = existing;
        ht->numCollisions++;
    }
    
    ht->array[index] = entry;
    ht->numEntries++;

    // check for grow
    if (!ht->growing) {
        grow(ht);
    }

    return oldNext;
}

void* find(table *ht, char *key) {
    assert(ht);
    assert(key);
    
    // hash into array
    unsigned long index = crc64(key) % ht->size;

    kv *existing = ht->array[index];

    while (existing) {
        if (!strcmp(existing->key, key)) {
            return existing->val;
        }
        existing = existing->next;
    }

    return NULL;
}

void freeTable(table *ht, void freeKey(void *__ptr), void freeVal(void *__ptr)) {
    assert(ht);

    // Free array entries
    for (unsigned long ii = 0; ii < ht->size; ii++) {
        // Free entries in linked list
        kv *entry = ht->array[ii];
        while (entry) {
            if (freeKey && entry->key) freeKey(entry->key);
            if (freeVal && entry->val) freeVal(entry->val);
            kv *next = entry->next;
            free(entry);
            entry = next;
        }
    }

    free(ht->array);
    free(ht);
}
