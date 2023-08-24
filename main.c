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

int main(int argc, char const *argv[])
{
    // must include at least one file name
    assert(argc > 1);

    unsigned long count = 0; // number of most-encountered word pairs to print
    short countEntered = 0; // whether the user has inputted a specified count

    table *ht = initTable(256);

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
            short toContinue = 0;
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

    if (countEntered) {
        // User entered a specified count
        printWordPairs(ht, count);
    } else {
        // Print all word pairs
        printAllWordPairs(ht);
    }

    freeTable(ht, free, free);

    return 0;
}
