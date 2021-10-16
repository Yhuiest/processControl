#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main()
{
    
    int value ;
    scanf("%d", &value);
    pid_t pid = fork();
    if (pid == 0)
    {
        while(value != 1)
        {
            printf("%d ", value);
            if(value % 2 == 0)
            {
                value /= 2;
            }
            else{
                value = value * 3 + 1;
            }
        }
        printf("1\n");
    }
    else if(pid > 0)
    {
        wait(NULL);
        exit(0);
    }
}