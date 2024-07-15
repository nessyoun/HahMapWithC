#include "hashmap.h"
#include <stdio.h>
#include <string.h>

// Default hash function
size_t default_hash_func(void* key) {
    size_t hash = 0;
    char* str = (char*) key;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash;
}

// Default key comparison function
int default_key_cmp(void* key1, void* key2) {
    return strcmp((char*) key1, (char*) key2);
}

// Initialize hashmap
Hashmap* hashmap_init(size_t capacity, size_t (*hash_func)(void*), int (*key_cmp)(void*, void*)) {
    Hashmap* map = (Hashmap*) malloc(sizeof(Hashmap));
    map->table = (Entry**) calloc(capacity, sizeof(Entry*));
    map->size = 0;
    map->capacity = capacity;
    map->hash_func = hash_func ? hash_func : default_hash_func;
    map->key_cmp = key_cmp ? key_cmp : default_key_cmp;
    return map;
}

// Create a new entry
Entry* create_entry(void* key, void* value) {
    Entry* entry = (Entry*) malloc(sizeof(Entry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    return entry;
}

// Insert key-value pair
void hashmap_insert(Hashmap* map, void* key, void* value) {
    size_t index = map->hash_func(key) % map->capacity;
    Entry* entry = map->table[index];
    if (!entry) {
        map->table[index] = create_entry(key, value);
    } else {
        while (entry->next) {
            if (map->key_cmp(entry->key, key) == 0) {
                entry->value = value;
                return;
            }
            entry = entry->next;
        }
        if (map->key_cmp(entry->key, key) == 0) {
            entry->value = value;
        } else {
            entry->next = create_entry(key, value);
        }
    }
    map->size++;
}

// Search for a key
void* hashmap_search(Hashmap* map, void* key) {
    size_t index = map->hash_func(key) % map->capacity;
    Entry* entry = map->table[index];
    while (entry) {
        if (map->key_cmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

// Delete a key
void hashmap_delete(Hashmap* map, void* key) {
    size_t index = map->hash_func(key) % map->capacity;
    Entry* entry = map->table[index];
    Entry* prev = NULL;
    while (entry) {
        if (map->key_cmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                map->table[index] = entry->next;
            }
            free(entry);
            map->size--;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

// Free the hashmap
void hashmap_free(Hashmap* map) {
    for (size_t i = 0; i < map->capacity; i++) {
        Entry* entry = map->table[i];
        while (entry) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
    free(map->table);
    free(map);
}
