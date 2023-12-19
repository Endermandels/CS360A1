# Assignment 1 - Counting Words Using a Hash Table

### CS 360

### Elijah Delavar

### 9/5/2023

## Files

main.c hash.c hash.h wordPairCounting.c wordPairCounting.h getWord.c getWord.h crc.c crc.h README.md Makefile

## Execution

Compiler used: gcc

To compile using Makefile:

    $ make

To clean up object files and executable:

    $ make clean

To run:

    $ ./pairsofwords <-count> filename1 <filename2> <filename3> ...

## Description

This program counts the occurances of subsequent word pairs in the specified files.

It then prints out a specified number of the most-encountered words using the <-count> option.
If <-count> is left out, all word pairs are printed out from most-encountered to least encountered.

This program uses a separate chaining hash table to store all word pairs and their occurances.
