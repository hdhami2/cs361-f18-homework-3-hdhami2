//hdhami2

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


void sigint ( int sig)
{ char text[] = "Caught SIGINT\n";
write(1, text, sizeof(text));
}

void sigstp (int sig){
	char text = "Caught SIGSTP\n";
	write (1, text, sizeof(text));
}



int main() {

signal(SIGINT, sigint);
signal(SIGTSTP, sigstp);
//create some space for our string
	
		
	char line[500];
	//char *word = strtok(line, " ");// break the string up into words	
	//char **args = (char **) malloc(sizeof(line)* sizeof(char*));


	while(1)   // when true
 	{
	int i = 0;  // word counter
	printf("361> ");   // required print statement
  	gets(line);	// insit and read the user input
	
	char *word = strtok(line, " ");// break the string up into words
  	char **args = (char **) malloc(sizeof(line)* sizeof(char*));

	while(word)
	{ 
	  strcpy(args[i], word);
	  //args[i] = word;
	  i= i+1;
	  word = strtok(NULL, " ");
	  
	}
	//exit command
	if (strcmp(args[0], "exit") == 0 ) 
	{
	  exit(0);
	}
	//checking if the array works
	//int j = 0;
 	//for (; j<i; j++)
	//{ printf("args[%d]: %s\n", j, args[j]);}
 	
	int pid = fork();	
	if(pid == 0)
	{ if(execvp(args[0],args) < 0)
	{ printf("ERROR\n"); exit(-1);}
	}
	
	else{
	printf("PID: %d.\n",pid);

	int status;
	wait(&status);
	printf("Exit: %d\n", WEXITSTATUS(status));
	}

}
}
