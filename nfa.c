// *********************************************
// *********************************************
// ** Name: nfa.c (CS 317 project)
// ** Author: Bradley Dowling
// **
// ** Description: nfa.c holds all functions needed to
// ** create and destroy NFAs. See nfa.h for a more
// ** detailed description of each function.
// **

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "nfa.h"
#include "stack.h"

NFA *createNFA(int start, int accept) {
	NFA *newNFA = malloc(sizeof(NFA));
	newNFA->startState = start;
	newNFA->acceptState = accept;
	newNFA->tranList = NULL;
	return newNFA;
}

Transition *createTransition(int q1, int q2, char i) {
	Transition *newTransition = malloc(sizeof(Transition));
	newTransition->fromState = q1;
	newTransition->toState = q2;
	newTransition->input = i;
	newTransition->next = NULL;
	return newTransition;
}

// equalTransition() checks to see if an existing transition is
// exactly equal to a given fromState, toState, and input
int equalTransition(Transition *t, int q1, int q2, char i) {
	return ( t->fromState == q1 && t->toState == q2 && t->input == i );
}

// addTransition() adds a transition to an NFA if it doesn't already exist
void addTransition(NFA *m, int q1, int q2, char i) {

	Transition *t_curr = m->tranList;
	if (t_curr == NULL) {
		// BASE CASE: this NFA has no transitions yet...
		m->tranList = createTransition(q1, q2, i);
		return;
	}

	// crawl through the list of transitions to see if the 
	// transition we want to add already exists...
	Transition *t_prev = t_curr;
	t_curr = t_curr->next;
	while (t_curr != NULL) {
		if (equalTransition(t_curr, q1, q2, i)) return; // transition already
								// in list.

		if (q1 < t_curr->fromState) {
			// insert location found
			t_prev->next = createTransition(q1, q2, i);
			t_prev->next->next = t_curr;
			return;
		}

		if (q1 == t_curr->fromState && q2 < t_curr->toState) {
			// insert location found
			t_prev->next = createTransition(q1, q2, i);
			t_prev->next->next = t_curr;
			return;
		}

		// if here, keep crawling...
		t_prev = t_curr;
		t_curr = t_curr->next;
	}

	// if here, transition from state is the largest one so far.
	// put it here at the end of the list...
	t_prev->next = createTransition(q1, q2, i);
	return;
}

// dumpNFA() prints the contents of an NFA, including the start state,
// accept state, and all transitions
void dumpNFA(NFA *m) {
	printf("Start: q%d\n", m->startState);
	printf("Accept: q%d\n", m->acceptState);

	// crawl through transitions...
	Transition *t_curr = m->tranList;
	while (t_curr != NULL) {
		printf("(q%d, %c) -> q%d\n", t_curr->fromState, t_curr->input, t_curr->toState);
		t_curr = t_curr->next;
	}
	printf("\n");
}

NFA *baseNFA(int q1, int q2, char i) {
	NFA *newNFA = createNFA(q1, q2); // create the new NFA

	// add transition between q1 and q2
	addTransition(newNFA, q1, q2, i);
	return newNFA;
}

NFA *unionNFA(NFA *m1, NFA *m2, int q1, int q2) {
	NFA *newNFA = createNFA(q1, q2); // create the new NFA

	// add transitions from m1:
	Transition *t_curr = m1->tranList;
	addTransition(newNFA, t_curr->fromState, t_curr->toState, t_curr->input);

	t_curr = t_curr->next;
	while (t_curr != NULL) {
		addTransition(newNFA, t_curr->fromState, t_curr->toState, t_curr->input);
		t_curr = t_curr->next;
	}

	// add transitions from m2:
	t_curr = m2->tranList;
	while (t_curr != NULL) {
		addTransition(newNFA, t_curr->fromState, t_curr->toState, t_curr->input);
		t_curr = t_curr->next;
	}
	
	// add new start state transitions
	addTransition(newNFA, q1, m1->startState, 'E');
	addTransition(newNFA, q1, m2->startState, 'E');

	// add new accept state transitions
	addTransition(newNFA, m1->acceptState, q2, 'E');
	addTransition(newNFA, m2->acceptState, q2, 'E');

	// done!
	return newNFA;
}

NFA *concatNFA(NFA *m1, NFA *m2) {
	NFA *newNFA = createNFA(m1->startState, m2->acceptState); // create the new NFA

	// add transitions from m1:
	Transition *t_curr = m1->tranList;
	addTransition(newNFA, t_curr->fromState, t_curr->toState, t_curr->input);

	t_curr = t_curr->next;
	while (t_curr != NULL) {
		addTransition(newNFA, t_curr->fromState, t_curr->toState, t_curr->input);
		t_curr = t_curr->next;
	}

	// add transitions from m2:
	t_curr = m2->tranList;
	while (t_curr != NULL) {
		addTransition(newNFA, t_curr->fromState, t_curr->toState, t_curr->input);
		t_curr = t_curr->next;
	}
	
	// add new transition between the NFA's
	addTransition(newNFA, m1->acceptState, m2->startState, 'E');

	return newNFA;
}

NFA *kleeneNFA(NFA *m1, int q0) {
	NFA *newNFA = createNFA(q0, q0);
	
	// add transitions from m1:
	Transition *t_curr = m1->tranList;
	addTransition(newNFA, t_curr->fromState, t_curr->toState, t_curr->input);

	t_curr = t_curr->next;
	while (t_curr != NULL) {
		addTransition(newNFA, t_curr->fromState, t_curr->toState, t_curr->input);
		t_curr = t_curr->next;
	}

	// add new transitions:
	addTransition(newNFA, m1->acceptState, q0, 'E');
	addTransition(newNFA, q0, m1->startState, 'E');
	return newNFA;
}

NFA *regexToNFA(char *input) {
	Stack *s = initStack();
	NFA *operand1;
	NFA *operand2;
	NFA *result;

	int i = 0;
	int state1 = 1;
	int state2 = 2;
	while (input[i] != '\0') {
		switch (input[i]) {
			case '|':
				if (s->TOS < 1) {
					// malformed regex
					// check if the stack has NFA still present
					// pop it then free it
					if (isEmpty(s) == 0) freeNFA((NFA *) pop(s));
					free(s);
					return NULL;
				}
				operand2 = (NFA *) pop(s);
				operand1 = (NFA *) pop(s);
				push(s, unionNFA(operand1, operand2, state1, state2));
				freeNFA(operand1);
				freeNFA(operand2);
				state1 += 2;
				state2 += 2;
				break;
			case '&':
				if (s->TOS < 1) {
					// malformed regex
					// check if the stack has NFA still present
					// pop it then free it
					if (isEmpty(s) == 0) freeNFA((NFA *) pop(s));
					free(s);
					return NULL;
				}
				operand2 = (NFA *) pop(s);
				operand1 = (NFA *) pop(s);
				push(s, concatNFA(operand1, operand2));
				freeNFA(operand1);
				freeNFA(operand2);
				break;
			case '*':
				if (isEmpty(s)) {
					// malformed regex
					free(s);
					return NULL;
				}
				operand1 = (NFA *) pop(s);
				push(s, kleeneNFA(operand1, state1));
				freeNFA(operand1);
				state1++;
				state2++;
				break;
			default:
				push(s, baseNFA(state1, state2, input[i]));
				state1 += 2;
				state2 += 2;
		}

		i++;
	}

	result = (NFA *) pop(s);

	// one final double check. If the regex is valid, the stack s should
	// be empty now.
	if (isEmpty(s) == 0) result = NULL;

	free(s);
	return result;
}

void freeNFA(NFA *m) {
	// start by freeing the malloc'd transitions
	Transition *t_curr = m->tranList;
	if (t_curr == NULL) {
		// empty transition list
		free(m);
		return;
	}

	// crawl through the transitions
	Transition *t_prev = t_curr;
	t_curr = t_curr->next;
	while (t_curr != NULL) {
		free(t_prev); // free the previous transition
		
		// crawl forward in the list
		t_prev = t_curr;
		t_curr = t_curr->next;
	}

	// free the last transition in the list
	free(t_prev);

	// now free the NFA
	free(m);
	return;
}
