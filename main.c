/*
Assignment 1
9/5/2023
CS 360
Elijah Delavar

Files:
    main.c hash.c hash.h wordPairCounting.c wordPairCounting.h getWord.c getWord.h crc.c crc.h README.md Makefile
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "wordPairCounting.h"
#define min(x,y) ((x)<(y))?(x):(y)


void parseArgs(table *ht, int argc, const char *argv[]) {
    unsigned long count = 0; // number of most-encountered word pairs to print
    short countEntered = 0; // whether the user has inputted a specified count

    // loop through args
    for (unsigned long ii = 1; ii < argc; ii++) {
        const char *arg = argv[ii];
        if (arg[0] == '-') {
            // -count must not be empty
            if (!arg[1]) {
                fprintf(stderr, "Count must contain a valid number\n");
                exit(1);
            }

            // -count must be first argument, if specified
            if (ii > 1) {
                fprintf(stderr, "Count must be first argument, if specified\n");
                exit(1);
            }

            // check if count is a valid number
            unsigned long len = strlen(arg);
            for (unsigned long jj = 1; jj < len; jj++) {
                if (arg[jj] < '0' || arg[jj] > '9') {
                    fprintf(stderr, "Count must only contain numerical digits\n");
                    exit(1);
                }
            }

            // register count
            count = atoi(arg+1); // arg+1 excludes '-'
            countEntered = 1;
        } else {
            readFile(ht, arg);
        }
    }

    if (countEntered) {
        // Print <count> word pairs
        printWordPairs(ht, min(count, ht->numEntries));
    } else {
        // Print all word pairs
        printWordPairs(ht, ht->numEntries);
    }
}

int main(int argc, char const *argv[])
{
    // must include at least one file name
    if (argc < 2) {
        fprintf(stderr, "Must include at least one file name\n");
        exit(1);
    }

    // create hash table
    table *ht = initTable(256, NULL);

    // read word pairs into hash table
    parseArgs(ht, argc, argv);

    // free hash table
    freeTable(ht, free, free);

    return 0;
}
