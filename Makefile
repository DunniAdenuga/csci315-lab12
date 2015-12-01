all: ishell ishell5

ishell:	ishell.c
	gcc -o ishell ishell.c -lreadline