# Regex to NFA

### Author: Bradley Dowling
### Email: bradley.dowling@wsu.edu

Files:
	- main.c: controls I/O for program
	- nfa.c: functions controlling creation/deletion of NFAs
	- nfa.h: prototypes/documentation for nfa.c functions and NFA/transition
                 data structres.
	- stack.c: implementation of stack data structure
	- stack.h: prototypes/documentation for stack.c functions and stack data
                   structures.

Compile the executable using the following command:

		 make

After compiling, the program can be executed using the following command:

		main *filename*

where *filename* is the name of a .txt file that contains a postfix regex on
each line (do not include '<' or '>' in the argument specifying the filename).

The executable only takes a single argument. If anything other than 1 argument
is provided, an error message will be sent to stderr and the program will exit. 

If the argument provided is not an accessible filename, an error message will
be sent to stderr and the program will exit.

If an invalid postfix regex is provided on a line in the <filename> file, a 
message will be sent to stdout and the program will exit. This includes any 
regex that contains characters not in the alphabet set (a, b, c, d, e, E).

Only NFA's built from valid postfix regex's will be printed to stdout.
