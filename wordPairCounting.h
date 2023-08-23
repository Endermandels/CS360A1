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
    unsigned int x;
} occ;

void readFile(table *ht, char *fn);
void printAllWordPairs(table *ht); // Print all entries in hash table
void printWordPairs(table *ht, unsigned long count); // Print out <count> of the most-encountered word pairs.


#endif