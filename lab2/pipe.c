/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: pipe.c
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(void)
{
        int     fd[2], nbytes, num=15; //fd[0]r=ead,fd[1]=write 
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);

        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                close(fd[0]); /* Child process closes up input side of pipe */

                write(fd[1], num, (strlen(string)+1)); /* Send "string" through the output side of pipe */
                exit(0);
        }
        else
        {
                close(fd[1]); /* Parent process closes up output side of pipe */

                nbytes = read(fd[0], readbuffer, sizeof(readbuffer)); /* Read in a string from the pipe */
                printf("Received string: %s", readbuffer);
        }

        return(0);
}

