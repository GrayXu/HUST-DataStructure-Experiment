#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;//make sure that it's a basic data type
typedef int Status;
#define TRUE 1
#define FALSE 0
#define OK 1
#define LISTINCREMENT 10 //step-length when growing and cutting
#define LIST_INIT_SIZE 20

typedef struct vertex {
	ElemType key;
	ElemType data;
	struct vertex * next;
	struct vertex * adj;
} Vertex;

typedef struct myqueue {
	int length;
	int listsize;
	Vertex ** head;
} Queue;

/*
	Initalize this queue with 100 size.
*/
Status initQueue(Queue ** qP) {
	Queue * q = (Queue *)malloc(sizeof(Queue));
	if (!q) return FALSE;
	*qP = q;
	q->length = 0;
	q->listsize = LIST_INIT_SIZE;
	q->head = (Vertex **)malloc(sizeof(Vertex*)*LIST_INIT_SIZE);
	return OK;
}

/*
	when this gragh is too large, we have to grow this list to support BFS
*/
void growList(Queue * q) {
	q->head = (Vertex **)realloc(q->head, q->listsize + sizeof(Vertex*)*LISTINCREMENT);
	q->listsize += LISTINCREMENT;
	if (q->head == NULL) exit(0);
}

/*
	on the other hand...cut its size.
*/
void cutList(Queue * q) {//Pay attention to the opportunity to avoid frequently cutting and growing
	q->head = (Vertex **)realloc(q->head, q->listsize - sizeof(Vertex*)*LISTINCREMENT);
	q->listsize -= LISTINCREMENT;
	if (q->head == NULL) exit(0);
}

/*
	add to the end
*/
void enQueue(Queue * q, Vertex * v) {
	Vertex ** verArray = q->head;
	if (q->length == q->listsize) {
		growList(q);
	}
	verArray[q->length] = v;
	q->length++;
}

/*
	delete item from the head position
	return the vertex dequeued
*/
Vertex * deQueue(Queue * q) {

	if (q->length == 0) return NULL;
	Vertex ** verArray = q->head;
	Vertex * returnVer = verArray[0];
	int i = 1;
	for (i = 1; i < q->length; i++) {
		verArray[i - 1] = verArray[i];//@override
	}
	q->length--;
	return returnVer;
}

//destroy queue and free memory
void destroyQueue(Queue * q) {
	free(q->head);
	free(q);
}
