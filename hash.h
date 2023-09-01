/*
Assignment 1
9/5/2023
CS 360
Elijah Delavar

Files:
    main.c hash.c hash.h wordPairCounting.c wordPairCounting.h getWord.c getWord.h crc.c crc.h README.md Makefile

Description:
    This file contains a hash table structure that allows other programs to perform the following operations:
    - Init Hash Table
    - Insert Key Value Pair
    - Find Key Value Pair with Key
    - Free Hash Table
    The hash table implements separate chaining using linked lists.
*/

#ifndef HASH
#define HASH

// Key-Value pair
typedef struct KV {
    char *key;
    void *val;
    struct KV *next; // next KV in linked list
} kv;

// Hash table
typedef struct TABLE {
    struct KV **array; // Array of KV entries
    unsigned long size; // Size of array
    double numCollisions; // Number of collisions
    unsigned long numEntries; // Total number of entries in hash table
    short growing; // Whether the table is growing
} table;

/*
Initialize a new hash table (or an existing hash table <ht>) with a size of <size>.
If <size> is 0, use the default size of 256.

@return initialized hash table
*/
table* initTable(unsigned long size, table *ht);

/*
Hash new entry into hash table.

@return <entry>'s old next pointer (used internally)
*/
kv* insert(table *ht, kv *entry);

/*
Get the value of the key-value pair indicated by the specified key <key> stored in the table <ht>.

@return val or NULL if val was not found
*/
void* find(table *ht, char *key);

/*
Free <ht> and all entries inside <ht>.
<freeKey> and <freeVal> will be used to free the keys and values, respectively, of each key-value pair.
Example: Use free() for char * and NULL for const char *.
*/
void freeTable(table *ht, void freeKey(void *__ptr), void freeVal(void *__ptr));

#endif