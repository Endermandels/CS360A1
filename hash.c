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

table* initTable(unsigned long size) {
    table *ht = NULL;
    while (!ht) ht = (table*)malloc(sizeof(table));

    ht->array = NULL;
    ht->avgNumCollisions = 0;
    ht->numEntries = 0;

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

void insert(table *ht, kv *entry, void *sameKey(void *v1, void *v2), 
        void freeKey(void *_ptr), void freeVal(void *_ptr)) {
    assert(ht);
    assert(entry);

    // hash into ht
    unsigned long index = crc64(entry->key) % ht->size;

    printf("inserting key <%s> at index <%ld>\n", entry->key, index);

    kv *existing = ht->array[index];
    if (existing) {
        // go to end of existing's linked list
        while (existing) {
            if (!strcmp(existing->key, entry->key)) {
                // perform sameKey on existing and entry values
                if (sameKey) existing->val = sameKey(existing->val, entry->val);
                if (freeKey && entry->key) freeKey(entry->key);
                if (freeVal && entry->val) freeVal(entry->val);
                free(entry);
                break;
            } else if (!existing->next) {
                // collision
                existing->next = entry;
                ht->numCollisions++;
                ht->numEntries++;
                break;
            }

            existing = existing->next;
        }
    } else {
        // add new entry to array
        ht->array[index] = entry;
        ht->numEntries++;
    }
}

// UNUSED
void *get(table *ht, char *key) {
    assert(ht);
    assert(key);

    // loop through table for key
    for (unsigned long ii = 0; ii < ht->size; ii++) {
        if (!strcmp(ht->array[ii]->key, key)) {
            return ht->array[ii];
        }
    }

    return NULL;
}

void freeTable(table *ht, void freeKey(void *__ptr), void freeVal(void *__ptr)) {
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
