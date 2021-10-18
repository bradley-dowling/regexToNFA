#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "nfa.h"
#include "stack.h"

// *********************************************************
// *********************************************************
// ** Name: Regex to NFA project (CS 317)
// ** Author: Bradley Dowling
// **
// ** Description: This program takes a .txt file with a regex
// ** in postfix form and converts it into an NFA, then prints
// ** the start state, accept state, and all transitions in the
// ** NFA. The NFA's are built using the functions within nfa.h
// ** and nfa.c. A stack is utilized to convert the post-fix
// ** regexs to NFA's. The stack functions are located in stack.h
// ** and stack.c.
// **

int main(int argc, char **argv) {

	// first, check if valid number of arguments provided
	if (argc != 2) {
		// invalid number of arguments provided
		fprintf(stderr, "%s usage error: expected 1 argument, provided %d\n", argv[0], argc - 1);
		return -1;
	}

	// attempt to open filepath provided by argument
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		// unable to open file...
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	char acceptedInput[] = "abcdeE&|*\n";

	int c; // character read by fp
	int i = 0; // index for placing characters in buffer
	char buffer[100]; // buffer to hold NFA postfix
	NFA *newNFA = NULL;
	
	// start reading file character by character
	c = fgetc(fp);
	while (c != EOF) {
		// check if the character read is valid input
		if (strchr(acceptedInput, (int) c) == NULL) {
			printf("Invalid input: %c\n", c);
			fclose(fp);
			return -1;
		}
		if ((char) c == '\n') {
			// end of line (NFA)
			buffer[i] = '\0';
			newNFA = regexToNFA(buffer);
			if (newNFA == NULL) {
				// invalid postfix regex provided
				// time to exit gracefully
				printf("Invalid regex provided: '%s'\n", buffer);
				fclose(fp);
				return -1;
			}

			// NFA successfully built, print the original postfix regex
			// then print out the start state, accept state, and all transitions
			// of the NFA
			printf("RE: %s\n", buffer);
			dumpNFA(newNFA);
			freeNFA(newNFA); // free the NFA and all transitions within it from memory

			i = 0; // reset buffer index for next line of file input
		} else {
			// add the character to the buffer
			buffer[i] = (char) c;
			i++;
		}

		c = fgetc(fp); // get the next character
	}

	// done, close the file...	
	fclose(fp);
	return 0;
}
