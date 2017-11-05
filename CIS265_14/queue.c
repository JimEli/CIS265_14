/*************************************************************************
* Title: (CIS265_14) Queue
* File: queue.c
* Author: James Eli
* Date: 9/15/2017
*
* Exercise# 1 on page 505 (100 points) - A queue is similar to a node, 
* except that items are added at one end but removed from the other in a 
* FIFO (first-in, first-out) fashion. Operations on a queue might include:
*   Inserting an item from the beginning of the queue
*   Removing an item from the beginning of the queue
*   Returning the first item in the queue (without changing the queue)
*   Returning the last item in the queue (without changing the queue)
*   Testing whether the queue is empty
* Write an interface for a queue module in the form of a header file named
* queue.h
*
* Follow the exercise description of the queue. Let's assume our queue stores 
* only integers.
*
* Implement the queue.h (declarations) and queue.c (implementation)
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141), using C
*      language options.
*
* Submitted in partial fulfillment of the requirements of PCC CIS-265.
*************************************************************************
* Change Log:
*   09/15/2017: Initial release. JME
*************************************************************************/
#include "queue.h"

// Internal function used to recursively print queue.
static void printBackwards(const Node);

// Individual node(s) of queue.
struct Node_ {
	struct Node_ *next; // Points to next node, or NULL.
	int value;          // Data item of node (integer).
};

// Queue structure.
struct Queue_ {
	struct Node_ *head; // Head node in queue, or NULL if empty.
	struct Node_ *tail; // Tail node in queue, or NULL if empty.
};

// Create new queue.
Queue createQueue(void) {
	Queue q = malloc(sizeof(struct Queue_));
	if (q == NULL)
		return NULL;

	q->head = q->tail = NULL;

	return q;
}

// Free queue and all of its nodes.
void destroyQueue(Queue q) {
	int i; // Discarded value.

	while (!emptyQueue(q))
		deQueue(q, &i);

	free(q);
}

// Add new node to head of queue.
bool enQueue(Queue q, const int value) {
	Node n = malloc(sizeof(struct Node_));
	if (n == NULL)
		return false;

	n->value = value; // Insert value.
	n->next = NULL;	  // No following node.

	if (q->head == NULL)
		// If queue is empty, this becomes the head.
		q->head = n;
	else
		// Otherwise, insert after previous tail. 
		q->tail->next = n;

	// Make this the new queue tail. 
	q->tail = n;

	return true;
}

// Remove queue node.
bool deQueue(Queue q, int *value) {
	if (emptyQueue(q))
		return false;

	// Get queue's first node.
	*value = q->head->value;

	// Remove first node in queue.
	Node n = q->head;
	q->head = n->next;
	if (emptyQueue(q))
		q->tail = NULL;

	free(n);

	// Return node's value.
	return true;
}

// Is queue empty?
int emptyQueue(const Queue q) {
	return (q->head == NULL);
}

// Return queue node count.
size_t sizeQueue(Queue q) {
	if (q == NULL)
		return 0;

	Node n = q->head; // Start of queue.
	int count = 0;

	// Walk the queue, counting nodes.
	while (n) {
		n = n->next;
		count++;
	}

	return count;
}

// Return head of queue.
Node headQueue(const Queue q) {
	return q->head;
}

// Return tail of queue.
Node tailQueue(const Queue q) {
	return q->tail;
}

// Return head of queue value or NULL if empty.
bool peekHeadQueue(const Queue q, int *value) {
	if (q->head != NULL) {
		*value = q->head->value;
		return true;
	}
	else
		return false;
}

// Return tail of queue value or NULL if empty.
bool peekTailQueue(const Queue q, int *value) {
	if (q->tail != NULL) {
		*value = q->tail->value;
		return true;
	}
	else
		return false;
}

// Print queue from head to tail.
void printFromHeadQueue(const Queue q) {
	for (Node n = q->head; n != NULL; n = n->next)
		fprintf(stdout, "%d ", n->value);
	fputs("\n", stdout);
}

// Print queue from tail to head (reverse).
void printFromTailQueue(const Queue q) {
	printBackwards(q->head);
	fputs("\n", stdout);
}

// Internal function used to recursively print queue in reverse.
static void printBackwards(const Node n) {
	if (n == NULL)
		return;

	printBackwards(n->next); // Recursive call.
	fprintf(stdout, "%d ", n->value);
}

