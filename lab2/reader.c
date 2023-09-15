#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fd, buf;
    char * myfifo = "/tmp/myfifo";
    
    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    read(fd, &buf, sizeof(buf));
    printf("Received: %d\n", buf);
    close(fd);

    return 0;
}


