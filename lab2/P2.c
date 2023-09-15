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

#include <fcntl.h>
#include <sys/stat.h>

int num;

void pipe_receiver(){
    int fd;
    char * myfifo = "/tmp/myfifo";
    
    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    read(fd, &num, sizeof(num));
    printf("Received: %d\n", num);
    close(fd);
}


void pipe_trasmitter(){
    int fd;
    char * myfifo = "/tmp/myfifo2";

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_WRONLY);
    write(fd, &num, sizeof(num));
    close(fd);

    /* remove the FIFO */
    unlink(myfifo);
}

int main(void)
{
        int     fd[2], nbytes; //fd[0]r=ead,fd[1]=write 
        pid_t   childpid;
        
        pipe_receiver();
        pipe(fd);

        if((childpid = fork()) == -1) //fork()>= 1 is parent, else is child.
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                close(fd[0]); /* Child process closes up input side of pipe */
                num += 7;
                printf("P2 - child (x + 7): %d\n", num);
                write(fd[1], &num, sizeof(num)); /* Send "string" through the output side of pipe */
                close(fd[1]);
                exit(0);
        }
        else
        {
                close(fd[1]); /* Parent process closes up output side of pipe */

                nbytes = read(fd[0], &num, sizeof(num)); /* Read in a string from the pipe */
                num *= 3;
                printf("P2 - parent (x * 3): %d\n", num);
                close(fd[0]);
                pipe_trasmitter();
        }

        return(0);
}

