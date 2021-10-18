// *****************************************
// *****************************************
// ** Name: stack.c (CS 317 project)
// ** Author: Bradley Dowling
// **
// ** Description: stack.c and stack.h hold the functions
// ** required to implement a generic stack that can take
// ** any data type. See stack.h for details on the specific
// ** functions.
// **

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

Stack *initStack(void) {
	Stack *newStack = malloc(sizeof(Stack));
	newStack->TOS = -1; // index of -1 indicates that the stack is empty
	return newStack;
}

int atMaxCap(Stack *s) {
	if (s->TOS == STACK_CAP - 1) return 1; // full stack
	else return 0; // stack not full
}

int isEmpty(Stack *s) {
	if (s->TOS == -1) return 1; // empty stack
	else return 0; // stack not empty
}

int push(Stack *s, void *d) {
	// first, check if stack is full
	if (atMaxCap(s)) return 0;

	// add 'd' to data array
	s->TOS++;
	s->data[s->TOS] = d;
	return 1;
}

void *pop(Stack *s) {
	// first, check if the stack is empty
	if (isEmpty(s)) return NULL;

	// return the current TOS
	void *d = s->data[s->TOS];
	s->TOS--;
	return d;
}
