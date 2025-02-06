#include <stdio.h> // standard input output
#include <stdlib.h> // memmory allcaction 
#include <assert.h> // debug purpose
#include <string.h> // for memmove funciton 

#define INITIAL_CAPACITY 4

typedef struct {
    int* data; // dynamic array list
    int size; // elements count
    int capacity; // capacity of the ArrayList
} ArrayList;

// function declaration
ArrayList* create_arrayList ();
void arrayList_destroy (ArrayList* list);
int arrayList_resize (ArrayList* list, int new_capacity);
void arrayList_append (ArrayList* list, int value);
void arrayList_print (ArrayList* list);
void arrayList_insert (ArrayList* list, int index, int value);
int arrayList_get (ArrayList* list, int index);
void arrayList_set (ArrayList* list, int index, int value);
void arrayList_remove (ArrayList* list, int index);

int main () {

    ArrayList* list = create_arrayList();

    arrayList_append (list, 12);
    arrayList_append (list, 22);
    arrayList_append (list, 32);
    arrayList_append (list, 42);

    arrayList_print (list);

    arrayList_append (list, 52);
    arrayList_append (list, 62);
    arrayList_append (list, 72);
    arrayList_append (list, 82);

    arrayList_print (list);

    arrayList_append (list, 92);
    arrayList_append (list, 02);
    arrayList_append (list, 23);
    arrayList_append (list, 24);
    arrayList_append (list, 22);

    arrayList_print (list);

    arrayList_insert (list,  4, 9);

    arrayList_print (list);

    int e4 = arrayList_get (list, 4);
    printf ("Element four is : %d", e4);

    arrayList_set (list, 4, 1);

    arrayList_print (list);
    
    arrayList_destroy (list);
}

// function definitions
ArrayList* create_arrayList() {
    ArrayList* list = (ArrayList *) malloc (sizeof (ArrayList));

    if (!list) {
        fprintf(stderr, "---------Memory allacted failed");
        exit (EXIT_FAILURE);
    }

    list->data = (int *) malloc (sizeof (int) * INITIAL_CAPACITY);

    if (!list->data) {
        free (list);
        fprintf(stderr, "---------Memory allacted failed");
        exit (EXIT_FAILURE);
    }

    list->size = 0;
    list->capacity = INITIAL_CAPACITY;

    printf("\n---------ArrayList created successfully\n");

    return list;
}

void arrayList_destroy (ArrayList* list) {
    if (list) {
        free (list->data);
        free (list);
        printf ("\n---------ArrayList destroyed successfully\n");
    }
}

int arrayList_resize (ArrayList* list, int new_capacity) {
    int* new_data = (int *) realloc (list->data, sizeof (int) * new_capacity);

    if (!new_data) {
        fprintf(stderr, "---------Memory allocated failed\n");
        return 1;
    }

    list->data = new_data;
    list->capacity = new_capacity;
    printf("\n---------ArrayList resized\nnew Capacity is : %d\n", list->capacity);

    return 0;
} 

void arrayList_append (ArrayList* list, int value) {

    if (list->size == list->capacity) {
       if (arrayList_resize (list, list->capacity * 2)) {
           fprintf(stderr, "---------Error! cannot resize\n");
           exit (EXIT_FAILURE);
       }
    }

    list->data[list->size++] = value;
}

void arrayList_print (ArrayList* list) {

    if (!list) {
        printf("\n---------Cannot print: list is Null!\n");
        return;
    } else {

        printf ("\nCurrent Status : \n");
        printf ("\tsize       :   %d\n", list->size);
        printf ("\tcapacity   :   %d\n", list->capacity);

        for (int i = 0; i < list->size; i++) {
            if (i == 0) {
                printf("\n[");
            }
            printf("%d", list->data[i]);
            if ( i != list->size -1) {
                printf(", ");
            }
            if (i == list->size -1) {
                printf("]\n\n");
            }
        }
    }
}

void arrayList_insert (ArrayList* list, int index, int value) {
    
    assert (index >= 0 && index <= list->size - 1);

    if (list->size == list->capacity) {
        if (arrayList_resize (list, list->capacity * 2)) {
            fprintf (stderr, "\n---------Cannot resize!\n");
            exit (EXIT_FAILURE);
        }
    }

    memmove (&list->data[index + 1], &list->data[index], sizeof (int) * (list->size - index)); // shift right the avlaue
    list->data[index] = value;
    list->size++; // increment the size 

    printf("---------Value inserted successfully \n");
}

int arrayList_get (ArrayList* list, int index) {

    assert (index >= 0 && index <= list->size - 1);

    return list->data[index];
}

void arrayList_set (ArrayList* list, int index, int value) {

    assert (index >= 0 && index <= list->size - 1);

    list->data[index] = value;
}

void arrayList_remove (ArrayList* list, int index) {
    
    assert (index >= 0 && index <= list->size - 1);

    // void memmove (void &dest, void &src, size_t n);
    memmove (&list->data[index], &list->data[index + 1], sizeof (int) * (list->size - index -1));
    list->size--;
}
