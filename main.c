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

int main(int argc, char const *argv[])
{
    // must include at least one file name
    if (argc < 2) {
        fprintf(stderr, "Insufficient number of arguments\n");
        exit(1);
    }

    unsigned long count = 0; // number of most-encountered word pairs to print
    short countEntered = 0; // whether the user has inputted a specified count

    table *ht = initTable(1);
    assert(ht);

    // loop through args
    for (int ii = 1; ii < argc; ii++) {
        char *arg = argv[ii];
        if (arg[0] == '-') {
            // -count must be first argument, if specified
            if (ii > 1) {
                // error
                fprintf(stderr, "-count must be first argument.  %s as arg %d\n", arg, ii);
                continue;
            } else {
                // register count
                count = atoi(arg+1); // arg+1 excludes '-'
                countEntered = 1;
            }
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

    freeTable(ht);

    return 0;
}
