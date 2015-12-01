all: ishell gshell

ishell:	ishell.c
	gcc -o ishell ishell.c -lreadline
gshell:	gshell.c
	gcc -o gshell gshell.c -lreadline