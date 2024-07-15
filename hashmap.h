#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>

// Entry structure
typedef struct Entry {
    void* key;
    void* value;
    struct Entry* next;
} Entry;

// Hashmap structure
typedef struct {
    Entry** table;
    size_t size;
    size_t capacity;
    size_t (*hash_func)(void* key);
    int (*key_cmp)(void* key1, void* key2);
} Hashmap;

// Default hash function
size_t default_hash_func(void* key);

// Default key comparison function
int default_key_cmp(void* key1, void* key2);

// Initialize hashmap
Hashmap* hashmap_init(size_t capacity, size_t (*hash_func)(void*), int (*key_cmp)(void*, void*));

// Insert key-value pair
void hashmap_insert(Hashmap* map, void* key, void* value);

// Search for a key
void* hashmap_search(Hashmap* map, void* key);

// Delete a key
void hashmap_delete(Hashmap* map, void* key);

// Free the hashmap
void hashmap_free(Hashmap* map);

#endif // HASHMAP_H
