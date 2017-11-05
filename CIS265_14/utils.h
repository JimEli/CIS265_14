// Utility functions header file.

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>

// Minimum and maximum allowable input range.
#define MIN_INPUT -100
#define MAX_INPUT 100
// Maximum input attempts before aborting.
#define MAX_INPUT_ATTEMPTS 3
// Text displayed as menu prompt.
#define MENU_TEXT   "\nProgram Menu:\n"                             \
	"1 - Insert an integer item at the end of the queue.\n"         \
	"2 - Remove an integer item from the beginning of the queue.\n" \
	"3 - Display first item in the queue.\n"                        \
	"4 - Display last item in the queue.\n"                         \
	"5 - Display the count of items in the queue.\n"                \
	"6 - Quit.\n"                                                   \
	"Enter 1 - 6: "

// Get integer.
bool getInteger(const char *prompt, const int min, const int max, int *value);
// Command entry handled here.
char fetchCommand(const char *commands);

#endif /* _UTILS_H_ */
