/*
Assignment 1
9/5/2023
CS 360
Elijah Delavar

Files: TODO

Description: TODO
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
void readFile(table *ht, char *fn);

/*
Convert the hash table <ht> to an array sorted in decreasing order of occurance.

@return sorted array
*/
kv** convertHashTableToSortedArray(table *ht);

/*
Print <size> entries in array in decreasing order of occurance.
*/
void printWordPairs(kv **arr, unsigned long size);

#endif