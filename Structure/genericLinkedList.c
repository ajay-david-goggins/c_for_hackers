#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedList {
    void *data;
    struct LinkedList *next;
} LinkedList;

LinkedList* createNode (void* element, size_t dataSize);
LinkedList* insertAtBeginning (LinkedList *head, void* element, size_t dataSize);
LinkedList* insertAtEnd (LinkedList *head, void *element, size_t dataSize);
LinkedList* insertAtPosition (LinkedList *head, void *element, size_t dataSize, int position);
LinkedList* deleteNode (LinkedList *head, void *key, size_t dataSize); // key is value stored in the data pointer
LinkedList* deleteAtPosition (LinkedList *head, int position);
int searchNode (LinkedList *head, void *key, size_t dataSize);
void freeList (LinkedList* head);  
void printIntList (LinkedList *head);
void printStringList (LinkedList *head);
void printCharList (LinkedList *head);
void printDoubleList (LinkedList *head);
void printFloatList (LinkedList *head);

int main () {
    int a = 10;
    int b = 20;
    int c = 30;
    int d = 40;
    int e = 50;
    LinkedList* head = createNode (&a, sizeof (int)); 

    head = insertAtEnd (head, &b, sizeof(int));
    head = insertAtEnd (head, &c, sizeof(int));
    head = insertAtEnd (head, &d, sizeof(int));
    head = insertAtEnd (head, &e, sizeof(int));

    printIntList (head);
    printf ("\n");
    int x = 25;
    head = insertAtPosition (head, &x, sizeof(int), 2);
    int y = 35;
    head = insertAtPosition (head, &y, sizeof(int), 4);
    int z = 45;
    head = insertAtPosition (head, &z, sizeof(int), 6);
    int aa = 55;
    head = insertAtEnd(head, &aa, sizeof(int));
    int bb = 15;
    head = insertAtPosition (head, &bb, sizeof(int), 1);

    printIntList (head);
    printf ("\n");
    
    int dd = 27;
    head = insertAtPosition (head, &dd, sizeof(int), 4);// i mistakely inserted 17 in the LinkedList
    int cc = 17;
    head = insertAtPosition (head, &cc, sizeof(int), 2);// i mistakely inserted 17 in the LinkedList

    printIntList (head);
    printf ("\n");

    // delete basked on key value
    head = deleteNode (head, &dd, sizeof(int));  

    // delete based on key value
    head = deleteAtPosition (head, 2);  

    printf ("After deleted two nodes \n");
    printIntList (head);
    printf ("\n");

    freeList (head);
    return 0; 
}

LinkedList* createNode (void* element, size_t dataSize) {
    LinkedList *newNode = (LinkedList *) malloc (sizeof (LinkedList)); // create a newnodea for LinkedList

    if (!newNode) {
        fprintf (stderr, "Memory allocation failed\n");
        exit (EXIT_FAILURE);
    }

    newNode->data = malloc (dataSize);

    if (!newNode->data) {
        free (newNode);
        fprintf (stderr, "Memory allocation failed\n");
        exit (EXIT_FAILURE);
    }

    memcpy (newNode->data, element, dataSize);
    newNode->next = NULL;
    printf("New Node created successfully\n");

    return  newNode;
}

LinkedList* insertAtBeginning (LinkedList *head, void* element, size_t dataSize) {
    LinkedList *newNode = createNode (element, dataSize);
    newNode->next = head; // set the old node address to the newNode-> next 
    printf("NewNode insert at the beginning of the LInkedList\n");

    return newNode;
}

LinkedList* insertAtEnd (LinkedList *head, void *element, size_t dataSize) {
    LinkedList *newNode = createNode (element, dataSize);

    if (!head) return newNode;  // if head is null than return the new node 

    LinkedList *temp = head;
    while (temp->next) { // iterate over the end of the LinkedList
        temp = temp->next;
    }

    temp->next = newNode;
    printf("New node append at the end of the LInkedLIst\n");

    return head;
}

LinkedList* insertAtPosition (LinkedList *head, void *element, size_t dataSize, int position) {
    if (position <= 0) return insertAtBeginning (head, element, dataSize);

    LinkedList *newNode = createNode(element, dataSize);
    LinkedList *temp = head;
    for (int i = 0; i < position -1; i++) { // Iterate over to before the position node
       temp = temp->next;
    }

    newNode->next = temp->next;  // temp->next is hold the position address. we set the address to the new node next pointer
    temp->next = newNode;

    return head;
}

// delete a node by value
LinkedList* deleteNode (LinkedList *head, void *key,  size_t dataSize) {
    LinkedList *temp =  head, *prev = NULL;

    while (temp && memcmp (temp->data, key, dataSize) == 0) { // only if hte key present in first position
        head = temp->next; // if it find the key at 0 position it will remove the node and set the head to the next node
        free (temp->data);
        free (temp);
        return head; 
    }

    while (temp && memcmp (temp->data, key, dataSize) != 0) {
        prev = temp; // it will store the previous node of key value's node
        temp = temp->next; // i want to delete this node (while is stop when the loop is find the kye in the node)
    }

    if (!head) return NULL;

    prev->next = temp->next; // set the targe node after node address to the target node's previous node next pointer . after free the memory of the node
    free (temp->data);
    free (temp);

    return head;
}

// delete a node by position 
LinkedList* deleteAtPosition (LinkedList *head, int position) {
    if (!head) return NULL;

    LinkedList *temp = head;

    if (position == 0) {
        head = temp->next; // set the value of next node address to the head;
        free (temp->data);
        free (temp);
        return head;
    }

    LinkedList *prev;

    for (int i = 0; i < position - 1; i++) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = temp->next;// address of the next position
    free (temp->data);
    free (temp);

    return head;
}

int searchNode (LinkedList *head, void *key, size_t dataSize) {
    int position = 0;
    while (head) {
        if (memcmp (head->data, key, dataSize) == 0) 
            return position;
        head = head->next;
        position++;
    }

    printf ("Node does not found\n");
    return -1; // indication.
}

// free the entire list
void freeList (LinkedList* head) {
    while (head) {
        LinkedList *temp = head;
        head = head->next;
        free (temp->data);
        free (temp);
    }
    
    printf ("LinkedList freed successfully\n");
}

void printIntList (LinkedList *head) {
    printf ("[ [head] ->");

    while (head) {
        printf ("[%d] -> ", *(int *)head->data);
        head = head->next;
    }

    printf("[NULL] ]\n");
}

void printFloatList (LinkedList *head) {
    printf ("[ [head] ->");

    while (head) {
        printf ("[%f] -> ", *(float *)head->data);
        head = head->next;
    }

    printf("[NULL] ]\n");
}
 
void printDoubleList (LinkedList *head) {
    printf ("[ [head] ->");

    while (head) {
        printf ("[%lf] -> ", *(double*)head->data);
        head = head->next;
    }

    printf("[NULL] ]\n");
}

void printCharList (LinkedList *head) {
    printf ("[ [head] ->");

    while (head) {
        printf ("[%c] -> ", *(char*)head->data);
        head = head->next;
    }

    printf("[NULL] ]\n");
}

void printStringList (LinkedList *head) {
    printf ("[ [head] ->");

    while (head) {
        printf ("[%s] -> ", (char*)head->data);
        head = head->next;
    }

    printf("[NULL] ]\n");
}

