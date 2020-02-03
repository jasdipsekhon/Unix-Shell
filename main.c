//
//  main.c
//  unixShell5
//
//  Created by Jasdip Sekhon on 3/23/19.
//  Copyright © 2019 Jasdip Sekhon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define DELIMS "\t\r\n"
#define MAX 2048

int main(int argc, char *argv[])
{  
    char *cmd;
    char cmd_line[MAX];
    while (1)
    {             
        printf("$$ ");
        
        
        // wait to read
        // if no stream of characters read, break
        //char* fgets (char* str, int num, FILE* stream );
        // makes it so '$$' is not repeatedly printed
        if (!fgets(cmd_line, MAX, stdin))
        {
            break;
        }
        
        
        // points to string that represents program name; invoked by execvp
        argv[0] = cmd_line;
        

        // read
        // read command
        // breaks string str into a series of tokens using the delimiter delim.
        if ((cmd = strtok(cmd_line, DELIMS)))
        {
    
            //if user types exit, end program
            if (strcmp(cmd, "exit") == 0)
            {
                //indicates successful program termination
                exit(0);
                break;
            }
                  
            
            //child process
            //fork() returns -1 if it fails, and if it succeeds, it returns the forked child's pid in the parent, and 0 in the child
            if (fork() == 0)
            {
                //execute child
                //replaces the current running process with a new process
                execvp(argv[0], argv);
                //indicates successful program termination
                exit(0);
            }
            //parent process
            else
            {
                //wait until child completes its execution
                wait(0);
            }        
        }
    }
    return 0;
}

