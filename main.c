#include <stdio.h>
#include <stdlib.h>
#define ASCII_MAX_LEN 128
#define N 13

typedef struct _hashElement {
    int key;
    float value;
} HashElement;

typedef struct _hashTable {
    HashElement **elements;
    int size;
    int numberOfElements;
} HashTable;

HashElement *createElement(int key, float value) {
    HashElement *hashElement = (HashElement*)malloc(sizeof(HashElement));

    hashElement->key = key;
    hashElement->value = value;

    return hashElement;
}

HashTable *createTable(int size) {
    int i; 
    HashTable *hashTable = (HashTable*)malloc(sizeof(HashTable));

    hashTable->size = size;
    hashTable->numberOfElements = 0;
    hashTable->elements = (HashElement**)malloc(hashTable->size * sizeof(HashElement*));

    for (i = 0; i < hashTable->size; i++) {
        hashTable->elements[i] = NULL;
    }

    return hashTable;
}

int displayMenu(HashTable *table);
int hashCode(int key);
int searchTable(HashTable *table, int key);
void insertTable(HashTable *table, int key, float value);
void removeTable(HashTable *table, int key);
void displayTable(HashTable *table);
int handleAsciiImage();
void printAsciiImage(FILE *fptr);
void freeHashElement(HashElement *element);
void freeHashTable(HashTable *table);

int main() {

    HashTable *table = createTable(N);

    displayMenu(table);

    freeHashTable(table);
    
    return 0;
}

int displayMenu(HashTable *table) {
    int choice;
    int stopChoice;

    int key;
    float value;

    do {
        // Limpar tela
        system("cls");

        handleAsciiImage();

        printf("\n1. Add new value to table...\n");
        printf("\n2. Remove value from table...\n");
        printf("\n3. Search value in table...\n");
        printf("\n4. Show table...\n");
        printf("\n5. Shutdown...\n");
        printf("\nYour choice: ");
        scanf("%d", &choice);

        system("cls");

        switch(choice) {

            case 1:

                printf("\nKey: ");
                scanf("%d", &key);

                printf("\nValue: ");
                scanf("%f", &value);
                insertTable(table, key, value);
                break;
            case 2:
                printf("\nKey: ");
                scanf("%d", &key);

                removeTable(table, key);
                break;
            case 3:
                printf("\nKey: ");
                scanf("%d", &key);

                searchTable(table, key);
                break;
            case 4:
                displayTable(table);
                break;
            case 5:
                return 1;
                break;
            default:
                printf("\nInvalid choice!");
                break;
        }

        printf("\nDo you want to continue? (type 1 for 'Yes') ");
        scanf("%d", &stopChoice);
    } while (stopChoice == 1);

    return 0;
}

int hashCode(int key) {
    return key % N;
}

int searchTable(HashTable *table, int key) {

    int hashAddress = hashCode(key);

    while (table->elements[hashAddress] != NULL) {
        if (table->elements[hashAddress]->key == key) {
            printf("\n[key: %d, value: %f]\n", table->elements[hashAddress]->key, table->elements[hashAddress]->value);
            return 1;
        }

        hashAddress++;
        hashAddress %= N;
    }

    printf("\nNot found!\n");

    return 0;
}

void insertTable(HashTable *table, int key, float value) {

    HashElement *hashElement = createElement(key, value);

    hashElement -> key = key;
    hashElement -> value = value;

    int hashAddress = hashCode(key);

    // Check while value in table is not null and key is not repeated 
    while(table->elements[hashAddress] != NULL && table->elements[hashAddress] -> key != key) {
        if (table->numberOfElements == table->size) {
            printf("\nTable full!\n");
            break;
        }

        hashAddress++;
        hashAddress %= N;
    }

    if (table->elements[hashAddress] == NULL) {
        table->numberOfElements++;
    }

    table->elements[hashAddress] = hashElement;
}

void removeTable(HashTable *table, int key) {
    int hashAddress = hashCode(key);

    if(table->elements[hashAddress] == NULL) {
        printf("\nChave não encontrada!\n");

    } else if (table->elements[hashAddress]->key == key) {
        table->elements[hashAddress] = NULL;
        table->numberOfElements--;

        // Free space in memory 
        freeHashElement(table->elements[hashAddress]);
    }

}

void displayTable(HashTable *table) {
    int i;

    for (i = 0; i < table->size; i++) {
        if (table->elements[i] != NULL) {
            printf("\n[%d, %f]\n", table->elements[i]->key, table->elements[i]->value);
        } else {
            printf("\n[\t]\n");
        }

    }
}

int handleAsciiImage() {

  char *filename = "hash-tables-ascii.txt";
    FILE *fptr = NULL;

    if((fptr = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }

    printImage(fptr);

    fclose(fptr);
    
    return 0;
}

void printAsciiImage(FILE *fptr) {
 char read_string[ASCII_MAX_LEN];

    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string); 
}

void freeHashElement(HashElement *element) {
    free(element);
}

void freeHashTable(HashTable *table) {
    int i; 
    // Free memory of all elements in hash table
    for (i = 0; i < table->size; i++) {
        HashElement *element = table->elements[i];
        if(element != NULL) {
            freeHashElement(element);
        }
    }

    free(table->elements);
    free(table);
}