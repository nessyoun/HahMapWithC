#include <stdio.h>
#include "hashmap.h"

int main() {
    Hashmap* map = hashmap_init(100, NULL, NULL);

    char* key1 = "key1";
    char* value1 = "value1";
    hashmap_insert(map, key1, value1);

    char* key2 = "key2";
    char* value2 = "value2";
    hashmap_insert(map, key2, value2);

    printf("Search key1: %s\n", (char*)hashmap_search(map, key1));
    printf("Search key2: %s\n", (char*)hashmap_search(map, key2));

    hashmap_delete(map, key1);
    printf("Search key1 after deletion: %s\n", (char*)hashmap_search(map, key1));

    hashmap_free(map);
    return 0;
}
