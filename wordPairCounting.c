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

int readFile(table *ht, char *fn) {
    if (!fn) {
        fprintf(stderr, "NULL Pointer: %s: %d\n", __FILE__, __LINE__);
        return 1;
    }

    FILE *fd = fopen(fn, "r");
    if (!fd) {
        fprintf(stderr, "NULL Pointer: %s: %d\n", __FILE__, __LINE__);
        return 1;
    }

    char *w1 = getNextWord(fd);
    char *w2 = NULL;

    int TEMP = 100;
    // Read Word Pairs
    while (1) {
        w2 = getNextWord(fd);

        if (!w2) {
            // EOF
            break;
        }

        // Init entry
        kv *entry = NULL;
        entry = (kv*)malloc(sizeof(kv));
        assert(entry);

        entry->key = NULL;
        entry->val = NULL;
        entry->next = NULL;

        occ *count = NULL;
        count = (occ*)malloc(sizeof(occ));
        assert(count);
        count->x = 1;
        entry->val = count;

        char *temp = NULL;
        temp = (char*)malloc(sizeof(char)*(strlen(w1) + strlen(w2) + 2));
        assert(temp);
        strcpy(temp, w1);
        strcat(temp, " "); // Possible error: no end '\0'
        strcat(temp, w2);
        puts(temp);
        
        entry->key = temp;

        insert(ht, entry);

        free(w1);
        w1 = w2;
    }

    if (w1){
        free(w1);
    }

    fclose(fd);
    return 0;
}

void printAllWordPairs(table *ht) {
    puts("Word Pairs");
}

void printWordPairs(table *ht, unsigned long count) {
    for (unsigned long ii = 0; ii < count; ii++){
        puts("Word Pairs");
    }
}