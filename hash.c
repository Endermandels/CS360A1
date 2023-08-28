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
#include "crc64.h" // Contains hash code function
#include "hash.h"

table* initTable(unsigned long size, table *ht) {
    if (!ht) {
        while (!ht) ht = (table*)malloc(sizeof(table));
    }

    ht->array = NULL;
    ht->avgNumCollisions = 0;
    ht->numCollisions = 0;
    ht->numEntries = 0;
    ht->growing = 0;

    if (size == 0) {
        ht->size = 256;
    } else {
        ht->size = size;
    }

    while (!ht->array) ht->array = (kv**)malloc(sizeof(kv*)*ht->size);

    for (unsigned long ii = 0; ii < ht->size; ii++) {
        ht->array[ii] = NULL;
    }

    return ht;
}

kv* insert(table *ht, kv *entry) {
    assert(ht);
    assert(entry);

    // save entry's next for easier growing
    kv *oldNext = entry->next;
    entry->next = NULL;

    // hash into ht
    unsigned long index = crc64(entry->key) % ht->size;

    kv *existing = ht->array[index];
    if (existing) {
        // go to end of existing's linked list
        while (existing) {
            if (!existing->next) {
                // Collision
                existing->next = entry;
                ht->numCollisions++;
                break;
            }
            existing = existing->next;
        }
    } else {
        // add new entry to array
        ht->array[index] = entry;
    }
    
    ht->numEntries++;

    // check for grow
    grow(ht);

    return oldNext;
}

void* find(table *ht, char *key) {
    assert(ht);
    assert(key);
    
    // hash into array
    unsigned long index = crc64(key) % ht->size;

    kv *existing = ht->array[index];

    if (existing) {
        while (existing) {
            if (!strcmp(existing->key, key)) {
                return existing->val;
            }
            existing = existing->next;
        }
    }

    return NULL;
}

void grow(table *ht) {
    assert(ht);
    
    // do not grow if already growing
    if (ht->growing) {
        return;
    }

    ht->avgNumCollisions = (float)(ht->numCollisions / ht->numEntries);

    if (ht->avgNumCollisions > 0.75) {
        // grow array
        kv **oldArr = ht->array;
        unsigned long oldSize = ht->size;
        initTable(ht->size*3, ht);
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
