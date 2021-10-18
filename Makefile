main: main.o stack.o nfa.o
	gcc -o main main.o stack.o nfa.o
main.o: main.c stack.h nfa.h
	gcc -c main.c
stack.o: stack.c stack.h
	gcc -c stack.c
nfa.o: nfa.c nfa.h
	gcc -c nfa.c
clean:
	rm main main.o stack.o nfa.o
