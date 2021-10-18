// ***********************************************
// ***********************************************
// ** Name: stack.h (CS 317 project)
// ** Author: Bradley Dowling
// **
// ** Description: stack.h and stack.c hold the functions
// ** required to implement a generic stack structure.
// ** The capacity of the stack is defined using the STACK_CAP
// ** definition. The stack keeps track of the index of the 
// ** top element in the list of void datapointers. Elements can
// ** be pushed onto the stack or popped from it.
// **

// Adjust the STACK_CAP definition as needed to change the size
// of the stack:
#define STACK_CAP 100

// Stack is a structure that keeps track of the overall capacity
// of a stack, the index of the element at the top of the stack
// and a list of void pointers that point to the various elements
// currently in the stack.
typedef struct _stack {
	int capacity;
	int TOS;
	void *data[STACK_CAP];
} Stack;

// Stack *initStack(void) allocates a new Stack structure in memory
// and returns a pointer to that stack.
Stack *initStack(void);

// int push(Stack *s, void *d) is a function that pushes a void pointer
// 'd' onto the top of the stack 's'. If first checks if the stack is full.
// If the stack is full, push will return a 0. If the stack is able to
// accomodate the pushed data, the function will return a 1.
int push(Stack *, void *);

// void *pop(Stack *s) is a function that will return a void pointer to the
// element at the top of the stack 's'. If will return NULL if the stack
// is already empty.
void *pop(Stack *);

// int isEmpty(Stack *s) is a function that checks to see if a stack 's' is
// empty. It returns a 1 if the stack is empty, and returns a 0 if it is not.
int isEmpty(Stack *);

// int atMaxCap(Stack *s) is a function that checks to see if a stack 's' is
// full. If the stack is full, the function will return a 1. If the stack is
// not full, the function will return a 0.
int atMaxCap(Stack *);
