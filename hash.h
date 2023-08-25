/*
Assignment 1
9/5/2023
CS 360
Elijah Delavar

Files: TODO

Description: TODO

functions:
    initTable(size)
    insert(KV)
    get(key)
    freeTable(table)
    grow()
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
    float avgNumCollisions; // Stat for when to grow table
    unsigned long numCollisions; // Stat for when to grow table
    unsigned long numEntries; // Stat for when to grow table
} table;

/*
Initialize a new hash table with a size of <size>.
If <size> is 0, use the default size of 256.

@return initialized hash table
*/
table* initTable(unsigned long size);

/*
Hash new entry into hash table.
If an entry in the hash table with the same key as the new entry already exists,
    perform <sameKey>, which should return the new value of the existing entry.
*/
void insert(table *ht, kv *entry, void *sameKey(void *v1, void *v2),
    void freeKey(void *_ptr), void freeVal(void *_ptr));

/*
Get the value indicated by the specified key stored in the table.
*/
void* get(table *ht, char *key);

/*
Free <ht> and all entries inside <ht>.
<freeKey> will be used to free the keys.
Use free() for char * and NULL for const char *.
*/
void freeTable(table *ht, void freeKey(void *__ptr), void freeVal(void *__ptr));

#endif