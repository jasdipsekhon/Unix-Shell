//
//  main.c
//  unixShell2
//
//  Created by Jasdip Sekhon on 3/22/19.
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
#define MAX 1024

/*static char* skipWhiteSpace(char* c)
{
    while (isspace(*c)) ++c;
    return c;
}
*/
int main(int argc, char *argv[])
{
    char *cmd;
    char cmd_line[MAX];
    
    while (1) {
        //printf("To exit type 'exit' \n");
        printf("$$ ");
        
        if (!fgets(cmd_line, MAX, stdin))
            break;
        argv[0] = cmd_line;
        
        if ((cmd = strtok(cmd_line, DELIMS))) {
            //cmd = skipWhiteSpace(cmd);
            if (strcmp(cmd, "exit") == 0)
            {
                exit(0);
                break;
            }
            if(fork() == 0)
            {
                if (strcmp(cmd, "cd") == 0)
                {
                    char *arg = strtok(0, DELIMS);
                    if (!arg)
                        fprintf(stderr, "argument missing \n");
                    else
                        chdir(arg);
                }
                else
                {
                    execvp(argv[0],argv);
                }
                exit(0);
            }
            else
            {
                wait(0);
            }
        }
    }
    return 0;
}
