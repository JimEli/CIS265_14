// Utility functions (input an integer & fetch menu command).
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

// Get integer.
bool getInteger(const char *prompt, const int min, const int max, int *value) {
	bool retVal = false; // Return true == success, assumed false.  
	char input[5];       // Holds user input as string.
	int i;               // Temporary holds input number.
	int attempts = MAX_INPUT_ATTEMPTS;

	while (attempts--) {
		// Prompt and grab user input.
		fprintf(stdout, prompt);
		if (!fgets(input, sizeof input, stdin)) {
			fputs("\nFatal program error!\n", stderr);
			return retVal;
		}
		else if (!strchr(input, '\n')) {
			// input too long, eat remaining characters.
			while (fgets(input, sizeof input, stdin) && !strchr(input, '\n'))
				; // Empty body.
			fputs("Too many characters input.\n", stdout);
		}
		else {
			// Catch special case of null input.
			if (strlen(input) <= 1)
				continue;
			// Attempt to convert from string to int, and validate.
			if (sscanf_s(input, "%d", &i)) {
				if (i >= min && i <= max) {
					*value = i;
					retVal = true;
					break; // Exit.
				}
				else
					fputs("Value entered is outside allowable range.\n", stdout);
			}
			else
				fputs("Invalid input.\n", stdout);
		}
	}
	return retVal; // Return integer value.
}

// Command entry handled here.
char fetchCommand(const char *commands) {
	// Prompt and grab user input.
	fputs(MENU_TEXT, stdout);
	char input = getchar();
	while (getchar() != '\n')
		; // clear remaining characters & newline.
	if (strchr(commands, input))
		return input;
	else
		return '\0';
}
