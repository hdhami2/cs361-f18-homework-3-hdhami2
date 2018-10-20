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






                                                                            // Lab5 sigint handling

void sigintHandler ( int sig )
{
    char msg[] = "Caught SIGINT\n";
    
    write(1, msg, sizeof(msg));
}




int main()
{
    signal(SIGINT, sigintHandler);
    
    
    char line[500];
    
    while(1)                        // while true
    {
        printf("361> ");                                        // command prompt
        
        gets(line);
        
        int i = 0;
        
        char *string = strtok(line, " ");                                   // Lab4 string parsing example
        
        char ** args = (char **) malloc(sizeof(line) * sizeof(char*));
        
        while(string)
        {
            args[i] = string;
            
            strcpy(args[i], string);
            
            string = strtok(NULL, " ");
            i++;
        }
        
        
        if (strcmp(args[0], "exit") == 0)                       // exit command
        {
            exit(0);
        }
        
        
        

        int pid = fork();                      //Lab4 exec/fork example
        
        
        if (pid == 0)
        {
            if(execvp(args[0], args) < 0)
            {
                printf("ERROR\n");
                exit(-1);
                
            }
        }
        
        else
        {
            printf("PID: %d\n", pid);
            int status;
            wait(&status);
            printf("Exit: %d\n", WEXITSTATUS(status));
        }
        
        
    }
}
