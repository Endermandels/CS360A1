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
#include "crc64.h" // Contains hash code function
#include "hash.h"

table* initTable(unsigned long size) {
    table *ht = NULL;
    ht = (table*)malloc(sizeof(table));
    if (!ht) {
        return NULL;
    }

    ht->array = NULL;
    ht->avgNumCollisions = 0;
    ht->numEntries = 0;

    if (size == 0) {
        ht->size = 256;
    } else {
        ht->size = size;
    }

    kv array[ht->size];
    ht->array = array;

    return ht;
}

void freeTable(table *ht) {
    free(ht);
}
