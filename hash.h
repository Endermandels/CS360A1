/*
Assignment 1
9/5/2023
CS 360
Elijah Delavar

Files: TODO

Description: TODO
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
    float avgNumCollisions; // Stat for when to grow table
    unsigned long numEntries; // Stat for when to grow table
    unsigned long size; // Size of array
} table;

/*
Initialize a new hash table with a size of <size>.
If <size> is 0, use the default size of 256.

@return initialized hash table
*/
table* initTable(unsigned long size);

/*
Insert new entry to hash table.

@return success (0), failure (1)
*/
int insert(table *ht, kv *entry);

/*
Free <ht> and all entries inside <ht>.
<freeKey> will be used to free the keys.
Use free() for char * and NULL for const char *.
*/
void freeTable(table *ht, void freeKey(void *__ptr));

#endif