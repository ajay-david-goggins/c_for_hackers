#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LinkedList {
	void *data;
	struct LinkedList *next;
	struct LinkedList *prev;
} LinkedList;

typedef struct {
	LinkedList *head;
	LinkedList *tail;
	int size;
} doublyLinkedList;

LinkedList* createNode (void *element, size_t eSize) { // eSize = element size
	LinkedList *newNode = (LinkedList *) malloc (sizeof (LinkedList));
	if (!newNode) {
		fprintf(stderr, "Memroy allcation failed");
		EXIT_FAILURE;
	} 

	newNode->data = malloc (eSize);
	if (!newNode->data) {
		fprintf(stderr, "Memory allocation failed");
		free(newNode);
		EXIT_FAILURE;
	}

	memcpy (newNode->data, element, eSize); // void memcpy (&dest, &src, size);
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

void insertAtBeginning (doublyLinkedList *list, void *element, size_t eSize) {
	LinkedList *newNode = createNode (element, eSize);

	if (!list->head) {
		list->head = newNode;
		list->tail = newNode;
	} else {
		newNode->next = list->head; // newnode next address to the head node
		list->head->prev = newNode; 
		list->head = newNode; // set the new node to the head
	}
	list->size++; // increase the size
}

void insertAtEnd (doublyLinkedList *list, void *element, size_t eSize) {
	LinkedList *newNode = createNode (element, eSize);

	if (!list->head) {
		list->head = newNode;
		list->tail = newNode;
	} else {
		list->tail->next = newNode;
		newNode->prev = list->tail;
		list->tail = newNode;
	}

	list->size++;
}

void insertAtPosition (doublyLinkedList *list, void *element, size_t eSize, int position) {
	if (position < 0) {
		insertAtBeginning(list, element, eSize);
		return;
	}

	if (position > list->size) {
		insertAtEnd(list, element, eSize);
		return;
	}

	LinkedList *newNode = createNode (element, eSize);
	LinkedList *temp = list->head;
	for (int i = 0; i < position - 1; i++) {
		if (!temp) return; // safety
		temp = temp->next;
	}

	newNode->next = temp->next;
	newNode->prev = temp;

	if (temp->next) {
		temp->next->prev = newNode;
	}

	temp->next = newNode;
	
}

void freeList (doublyLinkedList *list) {
	LinkedList *temp;
	while (list->head) {
		temp = list->head;
		list->head = list->head->next;

		free(temp->data);
		free(temp);
		list->size--;
	}
	list->tail = NULL;
}
 
void deleteAtPosition  (doublyLinkedList *list, int position) { // confusing
	if (position < 0 | position > list->size) {
		perror("Index out of bound error");
		exit;
	}

	int mid = list->size / 2;
	LinkedList *temp; 
	if (position >= 0 &&  position <= mid) {
		 temp = list->head;
		if (!temp) return;

		for (int i = 0; i < position; i++) {
			temp = temp->next;
		}

	} else {
		temp = list->tail;
		for (int i = list->size - 1; i > position; i--) {
			temp = temp->prev;
		}
	}

	if (temp->prev) {
		temp->prev->next = temp->next;
	} else {
		list->head = temp->next;
	}

	if (temp->next) 
		temp->next->prev = temp->prev;
	else 
		list->tail = temp->prev;

	free(temp->data);
	free(temp);
	list->size--;
}

int main() {
	return 0;
}
