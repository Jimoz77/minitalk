#include "talk.h"


void    handler(int signo, siginfo_t *info, void *more_info)
{



}





int main (void)
{
    printf("MY PID = %d\n", getpid());

    signal(SIGUSR1, handler, true);
    signal(SIGUSR2, handler, true);


    while()

    return EXIT_SUCCESS;
}