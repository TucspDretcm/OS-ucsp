#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

int x, band = 1;

void sighandler_random(int signum) {
  srand(time(NULL));
  x = (rand()%100) + 1;
  
  printf("random number is: %d\n", x);
  band = 0;
}

void pipe_receiver(){
    int fd;
    char * myfifo = "/tmp/myfifo2";

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    read(fd, &x, sizeof(x));
    printf("Received: %d\n", x);
    close(fd);
}

int main()
{
    int fd;
    char * myfifo = "/tmp/myfifo";

    printf("Run Program :D\n");
    
    signal(SIGUSR1, sighandler_random); // 16
    
    while (band) {
      sleep(1);
    }
    printf("sending data...\n");
    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    fd = open(myfifo, O_WRONLY);
    write(fd, &x, sizeof(x));
    close(fd);

    /* remove the FIFO */
    unlink(myfifo);
    sleep(1);
    pipe_receiver();

    return 0;
}

