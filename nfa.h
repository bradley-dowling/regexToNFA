// *********************************************
// *********************************************
// ** Name: nfa.h (CS 317 project)
// ** Author: Bradley Dowling
// **
// ** Description: nfa.h and nfa.c contain the functions
// ** that create and destroy NFA's. 4 types of NFA's can
// ** be built: a basic NFA that accepts a single character
// ** as input, a union NFA that is the union of two basic
// ** NFA's, and concatenated NFA that is the concatenation
// ** of two basic NFA's, and a kleene star NFA, which is 
// ** the kleene star of a basic NFA. regexToNFA() is also
// ** here, which builds a new NFA from a postfix regex
// ** by implementing a stack (see stack.h and stack.c).
// **


// Each NFA has one or more associated Transitions, which
// specify the character input needed to move from one 
// state (fromState) to another state (toState). Transitions
// can be found inside a list of transitions within an
// NFA (see below).
typedef struct _transition {
	int fromState;
	int toState;
	char input;
	struct _transition *next;
} Transition;

// An NFA is composed of a start state, an accept state, and
// list of transitions. Normal NFA's are also composed of a
// set of states and a set of characters which make up an
// alphabet, but neither of those are used within this
// implementation of an NFA structure.
typedef struct _nfa {
	int startState;
	int acceptState;
	Transition *tranList;
} NFA;

// NFA *createNFA(int start, int accept) is a function that allocates
// memory for a new NFA with a start state of 'start' and accept state
// of 'int'. It returns a pointer to that NFA.
NFA *createNFA(int, int);

// Transition *createTransition(int q1, int q2, char c) is a function
// that allocates memory for a new Transition with a from state of 'q1',
// a to state of 'q2', and an input character of 'c'. It returns a 
// pointer to that Transition.
Transition *createTransition(int, int, char);

// int equalTransition(Transition *m, int q1, int q2, char c) is a 
// function that compares a Transition structure 'm' to a given
// from state of 'q1', to state of 'q2' and input character 'c'. It 
// returns 1 if 'm' has those same states and input, and a 0 if not.
int equalTransition(Transition *, int, int, char);

// void addTransition(NFA *m, int q1, int q2, char c) is a function
// that creates a transition (using createTransition()) and adds it
// in ascending order to the list of transitions already present in 
// NFA 'm'. 
void addTransition(NFA *, int, int, char);

// void dumpNFA(NFA *m) is a function that prints out the start state,
// followed by the accept state, followed by every transition within
// an NFA 'm'. Output goes to stdout.
void dumpNFA(NFA *);

// NFA *baseNFA(int q1, int q2, char c) creates a basic NFA (using 
// createNFA()) with a start state of 'q1', an accept state of 'q2',
// and a single transition from the start state to the accept state
// with character 'c' (using createTransition()); It returns a pointer
// to the created NFA.
NFA *baseNFA(int, int, char);

// NFA *unionNFA(NFA *m1, NFA *m2, int q1, int q2) is a function
// that creates a new NFA (using createNFA()) with start state
// 'q1', accept state 'q2', and epsilon transitions from 'q1' to both
// start states of NFAs 'm1' and 'm2' and transitions from the accept
// states of 'm1' and 'm2' to q2. It returns a pointer to the create
// NFA.
NFA *unionNFA(NFA *, NFA *, int, int);

// NFA *concatNFA(NFA *m1, NFA *m2) is a function that creates a 
// new NFA (using createNFA()) with a start state equal to the 'm1'
// start, a transition from 'm1's accept state to 'm2's start
// state, and an overall accept state equal to 'm2's accept state.
// It returns a pointer to the NFA created.
NFA *concatNFA(NFA *, NFA *);

// NFA *kleeneNFA(NFA *m, int q1) is a function that creates a new
// NFA (using createNFA()) with a start state of 'q1', a transition from
// 'q1' to 'm's start state, a transition from 'm's accept state to 'q1', and 
// an overall accept state of 'q1'. It returns a pointer to the created
// NFA.
NFA *kleeneNFA(NFA *, int);

// NFA *regextoNFA(char *input) is a function that attempts to create an
// NFA from a null terminated string of characters that represent a
// postfix regex expression. It makes no assumption about the accepted characters
// other than the '&', '|', and '*' operators. If a valid regex is provided
// a pointer to the created NFA is returned. Otherwise, the function returns NULL.
NFA *regexToNFA(char *);

// void freeNFA(NFA *m) is a function that frees the NFA structure pointed to by
// 'm' as well as all allocated transitions within the NFA's Transition list.
void freeNFA(NFA *);
