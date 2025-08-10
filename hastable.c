#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

struct KeyValuePair {
    char key[50];
    char value[50];
    struct KeyValuePair* next;
};

struct HashTable {
    int size;
    struct KeyValuePair** table;
};

unsigned long hashFunction(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++) != '\0') {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

struct KeyValuePair* createKeyValuePair(const char* key, const char* value) {
    struct KeyValuePair* newPair = (struct KeyValuePair*)malloc(sizeof(struct KeyValuePair));
    if (newPair != NULL) {
        strcpy(newPair->key, key);
        strcpy(newPair->value, value);
        newPair->next = NULL;
    }
    return newPair;
}

struct HashTable* createHashTable(int size) {
    struct HashTable* newTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    if (newTable != NULL) {
        newTable->size = size;
        newTable->table = (struct KeyValuePair*)calloc(size, sizeof(struct KeyValuePair));
    }
    return newTable;
}

void insert(struct HashTable* hashTable, const char* key, const char* value) {
    unsigned long index = hashFunction(key) % hashTable->size;

    struct KeyValuePair* newPair = createKeyValuePair(key, value);

    newPair->next = hashTable->table[index];
    hashTable->table[index] = newPair;
}

const char* retrieve(struct HashTable* hashTable, const char* key) {
    unsigned long index = hashFunction(key) % hashTable->size;
    struct KeyValuePair* current = hashTable->table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return "Key not found";
}

void deleteKey(struct HashTable* hashTable, const char* key) {
    unsigned long index = hashFunction(key) % hashTable->size;
    struct KeyValuePair* current = hashTable->table[index];
    struct KeyValuePair* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                hashTable->table[index] = current->next;
            } else {
                prev->next = current->next;
            }

            free(current);
            return;
        }

        prev = current;
        current = current->next;
    }
}

void displayHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        printf("[%d] -> ", i);

        struct KeyValuePair* current = hashTable->table[i];
        while (current != NULL) {
            printf("(%s, %s) -> ", current->key, current->value);
            current = current->next;
        }

        printf("NULL\n");
    }
}

void freeHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        struct KeyValuePair* current = hashTable->table[i];
        while (current != NULL) {
            struct KeyValuePair* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(hashTable->table);
    free(hashTable);
}

int main() {
    struct HashTable* hashTable = createHashTable(TABLE_SIZE);

    insert(hashTable, "Red", "#ff0000");
    insert(hashTable, "Green", "#008000");
    insert(hashTable, "Blue", "#0000FF");
    insert(hashTable, "Yellow", "#FFFF00");
    insert(hashTable, "Orange", "#FFA500");

    printf("Initial Hash Table:\n");
    displayHashTable(hashTable);
    printf("\n");

    printf("Value for key 'Red': %s\n", retrieve(hashTable, "Red"));
    printf("Value for key 'Yellow': %s\n", retrieve(hashTable, "Yellow"));
    printf("Value for key 'White': %s\n", retrieve(hashTable, "White"));
    printf("\n");

    deleteKey(hashTable, "Green");

    printf("Hash Table after Deleting 'Green':\n");
    displayHashTable(hashTable);
    printf("\n");

    freeHashTable(hashTable);

    return 0;
}