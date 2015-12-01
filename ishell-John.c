/**
 * The feature I added was a one command memory. So if you type in '^' and press 
 * 'enter' ishell will execute the previous command. If there are no previous commands
 * nothing will be executed.
 **/

#include "wrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char* argv[]){
  char* command;
  char* prev = "";
  pid_t pid;
  int status;
  int s;
  while(1){
    //get input
    command = readline("ishell> ");
    
    if(strcmp(command, "^") == 0){
      if(strcmp(prev, "") != 0){
	command = prev;
	printf("Executing: %s\n", command);
      }else{
	prev = command;
      }
    }else{
      prev = command;
    }
    
    //check for double enter
    if(strlen(command) == 0){
      command = readline("ishell> ");
      if(strlen(command) == 0){
	pid = Fork();
	if(pid != 0){
	  Wait(&s);
	}else{
	  execl("/bin/ls", "/bin/ls", NULL);
	}
      }
    }

    //create child
    pid = Fork();

    if(0 != pid){
      //wait on child process
      Wait(&status);
      
      //
      if(0 == status){
	printf("[ishell: program terminated successfully]\n");
      }else{
	printf("[ishell: program terminated abnormally][%d]\n", status);
      }
    }else{
      //declare/initialize variables
      char* arg[16];
      char* delim = " ";
      char path[100];
      char* tok;
      int c = 1;

      //create begining of path
      strcat(path, "/bin/");
      
      //find first token
      delim = " ";
      tok = strtok(command, delim); 

      //set arg[0] to tok 
      strcat(path, tok);
      arg[0] = path;
      
      
      //second token 
      tok = strtok(NULL, delim);
      
      //get arguments
      if(tok != NULL){
	while(tok != NULL){
	  arg[c] = tok;
	  c++;
	  tok = strtok(NULL, delim);
	}
	//set last argument to NULL      
	arg[c+1] = NULL;
      }else{
	//sets second argument to NULL
	arg[c] = NULL;
      }

      //execute command and check for errors
      execv(arg[0], arg);
     
      return -1;
    }
  }
  

  return 0;
}
