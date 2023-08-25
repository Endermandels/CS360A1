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

kv *newEntry(char *w1, char *w2) {
        // Init entry
        kv *entry = NULL;
        while (!entry) entry = (kv*)malloc(sizeof(kv));

        entry->key = NULL;
        entry->val = NULL;
        entry->next = NULL;

        // Key
        char *temp = NULL;
        while (!temp) temp = (char*)malloc(sizeof(char)*(strlen(w1) + strlen(w2) + 2));

        // Join word 1 to word 2 with a space in between
        strcpy(temp, w1);
        strcat(temp, " ");
        strcat(temp, w2);

        entry->key = temp;

        // Occurance
        occ *count = NULL;
        while (!count) count = (occ*)malloc(sizeof(occ));
        count->x = 1;
        entry->val = count;

        return entry;
}

void* increaseOcc(void *v1, void *v2) {
    ((occ*)v1)->x += ((occ*)v2)->x;
    // TODO: Resize
    return v1;
}

void readWordPairs(table *ht, FILE *fd) {
    char *w1 = getNextWord(fd);
    char *w2 = getNextWord(fd);

    while (w2) {
        insert(ht, newEntry(w1, w2), increaseOcc, free, free);
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

void printAllWordPairs(table *ht) {
    for (unsigned long ii = 0; ii < ht->size; ii++) {
        kv *entry = ht->array[ii];

        // puts("test");

        while (entry) {
            printf("%10d %s\n", ((occ*)(((kv*)entry)->val))->x, entry->key);
            entry = entry->next;
        }
    }
}

void printWordPairs(table *ht, unsigned long count) {
    for (unsigned long ii = 0; ii < count; ii++){
        puts("Word Pairs");
    }
}