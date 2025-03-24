#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 	LinkedList{
	void *data;
	struct LinkedList *next, *prev; 
} LinkedList;

typedef struct {
	LinkedList *front;
	LinkedList *rear;
	size_t size;
} Deque;

Deque* createDeque (size_t size);
LinkedList* createNode (void *element, size_t eSize);
void insertFront(Deque *deque, void *element);
void insertRear (Deque *deque, void *element);
void deleteFront (Deque *deque);
void deleteRear (Deque *deque);
void* getFront(Deque *deque);
void* getRear(Deque *deque);
int isEmpty (Deque* deque);
void freeDeque(Deque *deque);
void printIntDeque(Deque *deque); //for printing integer only 
void printFloatDeque(Deque *deque); //for printing float and double 
void printCharDeque(Deque *deque);//for printing char only
void printStringDeque(Deque *deque);//for printing string only

int main() {
	Deque *deque = createDeque(sizeof(int));

	int a = 10, b = 20, c = 30, d = 40, e = 50;

	insertFront(deque, &a);
	insertRear(deque, &b);
	insertRear(deque, &c);
	insertRear(deque, &d);
	insertRear(deque, &e);

	printIntDeque(deque);

	deleteFront(deque);

	printf("\nAfter delete front node: ");

	printIntDeque(deque);

	printf("\nAfter delete rear node: ");

	deleteRear(deque);

	printIntDeque(deque);

	printf("\nDeque front data is : %d", *(int*) getFront(deque));

	printf("\nDeque front data is : %d", *(int*) getRear(deque));

	printf("\nInsert new value to front and rear");
	
	a = 2002;
	e = 2025;

	insertFront(deque, &a);
	insertRear(deque, &e);

	printIntDeque(deque);
	freeDeque(deque);

	return 0;
}

Deque* createDeque (size_t size) {
	Deque *deque = (Deque*) malloc(sizeof(Deque));

	if (!deque) {
	fprintf(stderr, "Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	deque->front = deque->rear = NULL;
	deque->size = size;

	return deque;
}

LinkedList* createNode (void *element, size_t eSize) {
	LinkedList *newNode = (LinkedList*) malloc (sizeof(LinkedList));
	if (!newNode) {
		fprintf(stderr,"Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	newNode->data = malloc(eSize);

	if (!newNode->data) {
		fprintf(stderr,"Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	memcpy(newNode->data, element, eSize);
	newNode->next = newNode->prev = NULL;
	return newNode;
}

void insertFront(Deque *deque, void *element) {
	LinkedList *newNode = createNode(element, deque->size);
	if (!deque->front) {
		 deque->front = deque->rear = newNode;
	} else {
		newNode->next = deque->front;
		deque->front->prev = newNode;
		deque->front = newNode;
	}
}

void insertRear (Deque *deque, void *element) {
	LinkedList *newNode = createNode(element, deque->size);
	if (!deque->rear) {
		deque->front = deque->rear = newNode;
	} else {
		newNode->prev = deque->rear;
		deque->rear->next = newNode;
		deque->rear = newNode;
	}
}

void deleteFront (Deque *deque) {
	if (!deque->front) return;
	LinkedList *temp = deque->front;
	deque->front = deque->front->next;

	if (deque->front) {
		deque->front->prev = NULL;

	} else {
		deque->rear = NULL;
	}
	free(temp->data);
	free(temp);
}

void deleteRear (Deque *deque) {
	if (!deque->rear) return;

	LinkedList *temp = deque->rear;
	deque->rear = deque->rear->prev;

	if (deque->rear) {
		deque->rear->next = NULL;
	} else {
		deque->front = NULL;
	}

	free(temp->data);
	free(temp);
}


void* getFront(Deque *deque) {
	return (deque->front) ? deque->front->data : NULL;
}

void* getRear(Deque *deque) {
	return (deque->rear) ? deque->rear->data : NULL;
}

int isEmpty (Deque* deque) {
	return deque->front == NULL;
}

void freeDeque(Deque *deque) {
	while (!isEmpty(deque)) {
		deleteFront(deque);
	}
	free(deque);
}
	
void printIntDeque(Deque *deque) {
	LinkedList *temp = deque->front;
	printf("\n\n[head] -> ");
	while (temp) {
		printf("[%d] -> ", *(int *)(temp->data));
		temp = temp->next;
	}
	printf("[rear]");
}


void printFloatDeque(Deque *deque) {
	LinkedList *temp = deque->front;
	printf("\n\n[head] -> ");
	while (temp) {
		printf("[%f] -> ", *(float *)(temp->data));
		temp = temp->next;
	}
	printf("[rear]");
}
void printCharDeque(Deque *deque) {
	LinkedList *temp = deque->front;
	printf("\n\n[head] -> ");
	while (temp) {
		printf("[%c] -> ", *(char *)(temp->data));
		temp = temp->next;
	}
	printf("[rear]");
}
void printStringDeque(Deque *deque) {
	LinkedList *temp = deque->front;
	printf("\n\n[head] -> ");
	while (temp) {
		printf("[%s] -> ", (char *)(temp->data));
		temp = temp->next;
	}
	printf("[rear]");
}
