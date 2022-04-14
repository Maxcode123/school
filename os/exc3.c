#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void main()
{
    pid_t pid0, pid1, pid2, pid3, pid4, pid5;
    int status1, status2, status3;

    pid0 = getpid();
    
    pid1 = fork();
    if (pid1 != 0)
    {
        // P0 code
        printf("Process P0 with PID, PPID: %d, %d\n", getpid(), getppid());
        pid2 = fork();
        if (pid2 == 0)
        {
            // P2 starts
            printf("Process P2 with PID, PPID: %d, %d\n", getpid(), getppid());
            pid3 = fork();
            if (pid3 != 0)
            {
                // P2 code
                pid4 = fork();
                if (pid4 != 0)
                {
                    // P2 code
                    pid5 = fork();
                    if (pid5 == 0)
                    {
                        // P5 starts
                        printf("Process P5 with PID, PPID: %d, %d\n", getpid(), getppid());
                        // P5 terminates
                    }
                    else
                    {
                        wait(&status2); // wait for child to finish
                        wait(&status3); // wait for child to finish
                        // P2 terminates
                    }
                }
                else
                {
                    // P4 starts
                    printf("Process P4 with PID, PPID: %d, %d\n", getpid(), getppid());
                    // P4 terminates
                }
            }
            else
            {
                // P3 starts
                printf("Process P3 with PID, PPID: %d, %d\n", getpid(), getppid());
                // P3 terminates
            }         
        }
    }
    else 
    {
        // P1 starts
        printf("Process P1 with PID, PPID: %d, %d\n", getpid(), getppid());
        // P1 terminates
    }

    if (getpid() == pid0)
    {
        // P0 code
        waitpid(pid2, &status1, 0); // wait for child P2 to finish
        execlp("ps", "ps", NULL);
        // P0 terminates
    }
}