/*************************************************************************
* Title: (CIS265_14) Queue
* File: main.c
* Author: James Eli
* Date: 9/15/2017
*
* A queue is similar to a element, except that items are added at one end but
* removed from the other in a FIFO (first-in, first-out) fashion. Operations
* on a queue might include:
*   Inserting an item from the beginning of the queue
*   Removing an item from the beginning of the queue
*   Returning the first item in the queue (without changing the queue)
*   Returning the last item in the queue (without changing the queue)
*   Testing whether the queue is empty
* Write an interface for a queue module in the form of a header file named
* queue.h
* Follow the exercise description of the queue. Let's assume our queue stores
* only integers. Your program should display a menu list to the user to select
* from:
*   1- Insert an integer item to the end of the queue
*   2- Remove an integer item from the beginning of the queue
*   3- Display first item in the queue
*   4- Display last item in the queue
*   5- Display the count of items in the queue
*   6- Quit the program
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
*   11/12/2017: Added removeQueueNode functionality. JME
*************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "utils.h"

// C/C++ Preprocessor Definitions: _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996) 

// Program starts here.
int main(void) {
	Queue queue; // Our test queue.
	
	// Attempt to create a new queue.
	if ((queue = createQueue()) == NULL) {
		fputs("Could not create a Queue.\n", stdout);
		exit(EXIT_FAILURE);
	}
	
	// Main command dispatch loop.
	while (1) {
		int i;  // Temporary holds queue values.

		switch (fetchCommand("1234567qQ")) {
		case '1': // Add item to queue.
			if (getInteger("\nEnter an integer: ", MIN_INPUT, MAX_INPUT, &i)) {
				enQueue(queue, i);
				fputs("Queue contents: ", stdout);
				printQueue(queue);
			}
			break;

		case '2': // Remove item from queue.
			if (deQueue(queue, &i))
				fprintf(stdout, "\nRemoved: %d from queue.", i);
			if (!sizeQueue(queue))
				fputs("\nQueue is empty.\n", stdout);
			else {
				fputs("\nQueue contents: ", stdout);
				printQueue(queue);
			}
			break;

		case '3': // Display head of queue.
			if (peekHeadQueue(queue, &i))
				fprintf(stdout, "\nHead of queue: %d\n", i);
			else
				fputs("\nQueue is empty.\n", stdout);
			break;

		case '4': // Display tail of queue.
			if (peekTailQueue(queue, &i))
				fprintf(stdout, "\nTail of queue: %d\n", i);
			else
				fputs("\nQueue is empty.\n", stdout);
			break;

		case '5': // Display size of queue.
			if (!(i = (int)sizeQueue(queue)))
				fputs("\nQueue is empty.\n", stdout);
			else
				printf("\nSize of queue: %d\n", i);
			break;

		case '6': // Search/remove item from queue.
			if (getInteger("\nEnter an integer: ", MIN_INPUT, MAX_INPUT, &i)) {
				if (removeQueueNode(queue, i)) {
					if (!sizeQueue(queue))
						fputs("\nQueue is empty.\n", stdout);
					else {
						fputs("Queue contents: ", stdout);
						printQueue(queue);
					}
				}
				else
					fprintf(stdout, "Node &d not found in Queue.\n");
			}
			break;

		case '7':
			/* no break */
		case 'q':
			/* no break */
		case 'Q': // Quit.
			fputs("\nTerminating program.\n", stdout);
			destroyQueue(queue);
			exit(EXIT_SUCCESS);
			break;

		case '\0':
			/* no break */
		default:
			// Unsupported command.
			fputs("\nUnsupported command entered.\n", stdout);
			break;
		}
	}
}

