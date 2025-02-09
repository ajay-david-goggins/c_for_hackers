#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Generic ArrayList structure
typedef struct {
    void **data;       // Array of void pointers to store elements
    size_t size;       // Current number of elements
    size_t capacity;   // Total allocated capacity
} ArrayList;

// Function to initialize the ArrayList
void initArrayList(ArrayList *list, size_t capacity) {
    list->data = malloc(capacity * sizeof(void *)); // Allocate memory for void* array
    list->size = 0;
    list->capacity = capacity;
}

// Function to add an element (generic)
void addElement(ArrayList *list, void *element, size_t elementSize) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->data = realloc(list->data, list->capacity * sizeof(void *)); // Expand memory
    }
    list->data[list->size] = malloc(elementSize); // Allocate memory for new element
    memcpy(list->data[list->size], element, elementSize); // Copy data
    list->size++;
}

// Function to get an element (returns void*)
void *getElement(ArrayList *list, size_t index) {
    if (index >= list->size) {
        printf("Index out of bounds!\n");
        return NULL;
    }
    return list->data[index];
}

// Function to set/replace an element at a given index
void setElement(ArrayList *list, size_t index, void *newElement, size_t elementSize) {
    if (index >= list->size) {
        printf("Index out of bounds!\n");
        return;
    }
    memcpy(list->data[index], newElement, elementSize);
}

// Function to remove an element at a given index
void removeElement(ArrayList *list, size_t index) {
    if (index >= list->size) {
        printf("Index out of bounds!\n");
        return;
    }

    free(list->data[index]); // Free memory of the removed element

    // Shift elements left
    for (size_t i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
    }

    list->size--; // Reduce size
}

// Function to clear the ArrayList
void clearArrayList(ArrayList *list) {
    for (size_t i = 0; i < list->size; i++) {
        free(list->data[i]); // Free each element
    }
    list->size = 0;
}

// Function to free ArrayList memory
void freeArrayList(ArrayList *list) {
    clearArrayList(list); // Free stored elements
    free(list->data); // Free main list storage
    list->capacity = 0;
}

// Function to print integer elements
void printIntList(ArrayList *list) {
    printf("ArrayList (size=%zu): ", list->size);
    for (size_t i = 0; i < list->size; i++) {
        printf("%d ", *(int *)list->data[i]);
    }
    printf("\n");
}

// Function to print string elements
void printStringList(ArrayList *list) {
    printf("ArrayList (size=%zu): ", list->size);
    for (size_t i = 0; i < list->size; i++) {
        printf("\"%s\" ", (char *)list->data[i]);
    }
    printf("\n");
}

int main() {
    // Initialize a list for integers
    ArrayList intList;
    initArrayList(&intList, 2);

    // Adding integers
    int a = 10, b = 20, c = 30;
    addElement(&intList, &a, sizeof(int));
    addElement(&intList, &b, sizeof(int));
    addElement(&intList, &c, sizeof(int));
    printIntList(&intList);

    // Get and print an integer element
    int *retrieved = (int *)getElement(&intList, 1);
    printf("Element at index 1: %d\n", *retrieved);

    // Set a new value at index 1
    int newValue = 50;
    setElement(&intList, 1, &newValue, sizeof(int));
    printIntList(&intList);

    // Remove an element
    removeElement(&intList, 0);
    printIntList(&intList);

    // Free the integer list
    freeArrayList(&intList);

    // ======================== STRING EXAMPLE ========================

    // Initialize a list for strings
    ArrayList strList;
    initArrayList(&strList, 2);

    // Adding strings (must allocate memory for strings)
    char *str1 = strdup("Hello");
    char *str2 = strdup("World");
    char *str3 = strdup("ArrayList");

    addElement(&strList, str1, strlen(str1) + 1);
    addElement(&strList, str2, strlen(str2) + 1);
    addElement(&strList, str3, strlen(str3) + 1);
    printStringList(&strList);

    // Get and print a string element
    char *retrievedStr = (char *)getElement(&strList, 2);
    printf("Element at index 2: %s\n", retrievedStr);

    // Remove a string
    removeElement(&strList, 1);
    printStringList(&strList);

    // Free string list
    freeArrayList(&strList);

    return 0;
}

