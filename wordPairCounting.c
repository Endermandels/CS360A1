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
#include "wordPairCounting.h"
#include "getWord.h"

/*
Read the file located at fn.
*/
void readFile(table *ht, char *fn) {
    assert(fn);

    FILE *fd = fopen(fn, "r");
    assert(fd);

    fclose(fd);
}

// Print all entries in hash table
void printAllWordPairs(table *ht) {
    puts("Word Pairs");
}

// Print out <count> of the most-encountered word pairs.
void printWordPairs(table *ht, unsigned long count) {
    for (unsigned long ii = 0; ii < count; ii++){
        puts("Word Pairs");
    }
}