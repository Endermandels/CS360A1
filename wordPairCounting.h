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
Print all entries in hash table in decreasing order of occurance.
*/
void printAllWordPairs(table *ht);

/*
Print out <count> of the most-encountered word pairs in decreasing order of occurance.
*/
void printWordPairs(table *ht, unsigned long count);


#endif