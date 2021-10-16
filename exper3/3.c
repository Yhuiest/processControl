#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 25
#define READ 0
#define WRITE 1
#define OFFSET 32

int main()
{
    char write_buffer[BUFFER_SIZE];
    char read_buffer[BUFFER_SIZE];
    int fd1[2];
    int fd2[2];
    pid_t pid;
    gets(write_buffer);

    if(pipe(fd1) == -1)
    {
        printf("Pipe failed");
        return 1;
    }
    if(pipe(fd2) == -1)
    {
        printf("Pipe failed");
        return 1;
    }

    pid = fork();
    if(pid > 0)
    {
        close(fd1[READ]);
        close(fd2[WRITE]);
        write(fd1[WRITE], write_buffer, strlen(write_buffer) + 1);
        read(fd2[READ], read_buffer, BUFFER_SIZE);
        close(fd2[READ]);
        close(fd1[WRITE]);
        printf("%s\n", read_buffer);
    }
    else if(pid == 0)
    {
        close(fd1[WRITE]);
        close(fd2[READ]);
        read(fd1[READ],read_buffer,BUFFER_SIZE);
        for(int i = 0; i < strlen(read_buffer); i++)
        {
            char c = read_buffer[i];
            if(islower(c))
            {
                read_buffer[i] = toupper(c);
            }
            else if(isupper(c))
            {
                read_buffer[i] = tolower(c);
            }
        }
        write(fd2[WRITE], read_buffer, strlen(read_buffer) + 1);
        close(fd2[WRITE]);
        close(fd1[READ]);
    }
    else
    {
        printf("Fork Failed");
    }
}