#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <wait.h>


int main()
{
    const int SIZE = 4096;
    const char * name = "OS";
    int value;
    int shm_fd;
    char * ptr = NULL;
    int pid = fork();
    int len;
    if(pid == 0)
    {
        scanf("%d", &value);
        shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);
        ftruncate(shm_fd,SIZE);
        ptr = mmap(NULL, SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, shm_fd, 0);
        while(value != 1)
        {
            len = sprintf(ptr, "%d ", value);
            ptr += len;
            if(value % 2 == 0)
            {
                value /= 2;
            }
            else{
                value = value * 3 + 1;
            }
        }
        sprintf(ptr, "1\n");
    }
    else if(pid > 0)
    {
        wait(NULL);
        shm_fd = shm_open(name, O_RDONLY, 0666);
        ptr = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        while(!(*ptr == '\n' || *ptr == EOF))
        {
            putchar(*ptr);
            ptr++;
        }
        printf("\n");
        shm_unlink(name);
        exit(0);
    }
}