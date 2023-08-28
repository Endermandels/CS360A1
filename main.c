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
#define min(x,y) ((x)<(y))?(x):(y)


void parseArgs(table *ht, int argc, char const *argv[]) {
    unsigned long count = 100; // number of most-encountered word pairs to print
    short countEntered = 0; // whether the user has inputted a specified count

    // loop through args
    for (unsigned long ii = 1; ii < argc; ii++) {
        char *arg = argv[ii];
        if (arg[0] == '-') {
            // -count must not be empty
            assert(arg[1]);

            // -count must be first argument, if specified
            assert(ii == 1);

            // check if count is a valid number
            unsigned long len = strlen(arg);
            for (unsigned long jj = 1; jj < len; jj++) {
                assert(arg[jj] >= '0' && arg[jj] <= '9');
            }

            // register count
            count = atoi(arg+1); // arg+1 excludes '-'
            countEntered = 1;
        } else {
            readFile(ht, arg);
        }
    }

    kv *arr = convertHashTableToSortedArray(ht);

    if (countEntered) {
        // Print <count> word pairs
        printWordPairs(arr, min(count, ht->numEntries));
    } else {
        // Print all word pairs
        printWordPairs(arr, ht->numEntries);
    }

    free(arr);
}

int main(int argc, char const *argv[])
{
    // must include at least one file name
    assert(argc > 1);

    table *ht = initTable(1, NULL);

    parseArgs(ht, argc, argv);

    freeTable(ht, free, free);

    return 0;
}
