#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Generic ArrayList
typedef struct {
    void **data; // Array of void pointer 
    size_t size; // number of element
    size_t capacity; // number of capacity
} ArrayList;

#define INITIAL_CAPACITY 4

// function declartion
ArrayList* init_arrayList ();
void arrayList_destroy (ArrayList* list);
void arrayList_append (ArrayList* list, void *element, size_t element_size);
void arrayList_printInteger (ArrayList* list);
void arrayList_printString (ArrayList *list); 
void arrayList_printDouble (ArrayList* list); 
void arrayList_printFloat (ArrayList* list); 
void arrayList_printChar (ArrayList* list); 
void* arrayList_get (ArrayList* list, int index);
void* arrayList_set  (ArrayList* list, int index, void *element, size_t element_size);
void arrayList_clear(ArrayList* list);
void arrayList_remove (ArrayList* list, int index);

int main () {
    ArrayList* list = init_arrayList();
    ArrayList* sL = init_arrayList();
    ArrayList* fL = init_arrayList();

    int n = 10;
    int m = 20;
    int p = 30;
    int r = 40;

    char *a = "ajay";
    char *b = "vijay";
    char *c = "raja";
    char *d = "sanjay";

    float e = 12.12f;
    float f = 22.12f;
    float g = 32.12f;
    float h = 42.12f;

    float updated_h = 82.11903f;

    arrayList_append (list, &n, sizeof (int));
    arrayList_append (list, &m, sizeof (int));
    arrayList_append (list, &p, sizeof (int));
    arrayList_append (list, &r, sizeof (int));

    arrayList_append (sL, a, strlen(a) + 1); // add 1 byte for \0
    arrayList_append (sL, b, strlen(b) + 1);
    arrayList_append (sL, c, strlen(c) + 1);
    arrayList_append (sL, d, strlen(d) + 1);

    arrayList_append (fL, &e, sizeof (float));
    arrayList_append (fL, &f, sizeof (float));
    arrayList_append (fL, &g, sizeof (float));
    arrayList_append (fL, &h, sizeof (float));

    printf ("Before Float vlaue in 3 index : %f\n", *(float *)arrayList_get (fL, 3));
    arrayList_set (fL, 3, &updated_h, sizeof (float));
    printf ("After Float vlaue in 3 index : %f\n", *(float *)arrayList_get (fL, 3));

    arrayList_printInteger (list);
    arrayList_printString (sL);
    arrayList_printFloat (fL);

    arrayList_remove (fL, 2);
    printf ("After removeing the 2 index ---");
    arrayList_printFloat (fL);

    arrayList_destroy (list);
    arrayList_destroy (sL);
    arrayList_destroy (fL);
    return 0;
}

ArrayList* init_arrayList () {
    ArrayList* list = malloc (sizeof (ArrayList));
     
    if (!list) {
        fprintf (stderr, "ArrayList Memory allocation failed\n");
        exit (EXIT_FAILURE);
    }

    list->data = malloc (sizeof (void *) * INITIAL_CAPACITY);

    if (!list->data) {
        free (list); // if it is fail free the ArrayList
        fprintf (stderr, "Array pointer memory allocation failed\n");
        exit (EXIT_FAILURE);
    }

    list->capacity = INITIAL_CAPACITY;
    list->size = 0; // set 0 because no element at the initiale stage
    printf("ArrayList created successfully \n");
     
    return list;
}

void arrayList_destroy (ArrayList* list) {
    if (list) {
        for (size_t i = 0; i < list->size; i++) {
            free (list->data[i]);
        }
        free (list->data);
        free (list);
        printf ("ArrayList destroyed successfully\n");
    }

}

void arrayList_append (ArrayList* list, void *element, size_t element_size) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = realloc (list->data, sizeof (void *) * list->capacity);
    }

    list->data[list->size] = malloc (element_size);
    memcpy (list->data[list->size], element, element_size);
    list->size++;
}

void arrayList_printInteger (ArrayList* list) {
    for (size_t i = 0; i < list->size; i++) {
        if (i == 0)
            printf ("[");

        printf("%d", *(int *)list->data[i]);

        if (i != list->size - 1) 
            printf (", ");
        else 
            printf("]\n");

    }
}

void arrayList_printString (ArrayList *list) {
    for (size_t i = 0; i < list->size; i++) {

        if (i == 0) 
            printf ("[");

        printf("%s", (char *)list->data[i]);
        if (i == list->size - 1) 
            printf ("]\n");
        else 
            printf(", ");
    }
}

void arrayList_printFloat (ArrayList* list) {
    for (int j = 0; j < list->size; j++) {
        
        if (j == 0) 
            printf("[");
        
        printf("%f", *(float *)list->data[j]);

        if (j != list->size -1) 
            printf(", ");
        else 
            printf("]\n");
    }
}

void arrayList_printChar (ArrayList* list) {
    for (int j = 0; j < list->size; j++) {
        
        if (j == 0) 
            printf("[");
        
        printf("%lf", *(char *)list->data[j]);

        if (j != list->size -1) 
            printf(", ");
        else 
            printf("]\n");
    }
}
void arrayList_printDouble (ArrayList* list) {
    for (int j = 0; j < list->size; j++) {
        
        if (j == 0) 
            printf("[");
        
        printf("%lf", *(double *)list->data[j]);

        if (j != list->size -1) 
            printf(", ");
        else 
            printf("]\n");
    }
}

void* arrayList_get (ArrayList* list, int index) {
    assert (index >= 0 && index <= list->size);

    return list->data[index];
}

void* arrayList_set  (ArrayList* list, int index, void *element, size_t element_size) {
    assert (index >= 0 && index <= list->size);

    memcpy (list->data[index], element, element_size); 
    // void memcpy (void* dest, void* src, size_t n);
}

void arrayList_clear(ArrayList* list) {

    for (size_t i = 0; i < list->size; i++) {
        free (list->data[i]); 
    }
    
    list->size = 0;
}

void arrayList_remove (ArrayList* list, int index) {
    
   if (index >= list->size) {
       fprintf (stderr, "Index out of bound!\n");
       return;
   } 

   free (list->data[index]);

   for (int i = index; i < list->size - 1; i++) {
        list->data[i] = list->data[i + 1];
   }

   list->size--; // reduce the size 
}
