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
#include <assert.h>
#include "crc64.h" // Contains hash code function
#include "hash.h"

table* initTable(unsigned long size) {
    table *ht = NULL;
    ht = (table*)malloc(sizeof(table));
    assert(ht);

    ht->array = NULL;
    ht->avgNumCollisions = 0;
    ht->numEntries = 0;

    if (size == 0) {
        ht->size = 256;
    } else {
        ht->size = size;
    }

    ht->array = (kv**)malloc(sizeof(kv*)*ht->size);
    assert(ht->array);

    for (unsigned long ii = 0; ii < ht->size; ii++) {
        ht->array[ii] = NULL;
    }

    return ht;
}

int insert(table *ht, kv *entry) {
    if (!ht) {
        fprintf(stderr, "NULL Pointer: %s: %d\n", __FILE__, __LINE__);
        return 1;
    }
    if (!entry) {
        fprintf(stderr, "NULL Pointer: %s: %d\n", __FILE__, __LINE__);
        return 1;
    }

    printf("key: %s\n", entry->key);

    ht->array[ht->numEntries++] = entry;
}

void freeTable(table *ht, void freeKey(void* __ptr)) {
    // Free array entries
    for (unsigned long ii = 0; ii < ht->size; ii++) {
        // Free entries in linked list
        kv *entry = ht->array[ii];
        while (entry) {
            if (entry->key && freeKey) {
                freeKey(entry->key);
            }
            if (entry->val) {
                free(entry->val);
            }

            kv *next = entry->next;
            free(entry);
            entry = next;
        }
    }

    free(ht->array);
    free(ht);
}
