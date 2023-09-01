/*
Assignment 1
9/5/2023
CS 360
Elijah Delavar

Files:
    main.c hash.c hash.h wordPairCounting.c wordPairCounting.h getWord.c getWord.h crc.c crc.h README.md Makefile

Description:
    This file contains functions which:
    - retrieve word pairs from text files and store those word pairs in a hash table
    - print word pairs from a hash table in descending order of occurrance
*/

#ifndef WPC
#define WPC

#include "hash.h"

// Occurances of a word pair
typedef struct OCCURANCES {
    unsigned long x;
} occ;

/*
Read the file located at fn.
Load word pairs as key-value pairs into hashtable <ht>.
*/
void readFile(table *ht, const char *fn);

/*
Print <size> entries of hash table <ht> in decreasing order of occurance.
*/
void printWordPairs(table *ht, unsigned long size);

#endif