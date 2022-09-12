#include "apue.h"

int main(void) 
{
	pid_t pid;

    fprintf(stderr, "print me only once!");
    //printf("print me only once!\n");
    //fflush(stdout);

    pid = fork();
    pid = fork();
    pid = fork();

    printf("pid = %d\n", getpid());

    exit(0);
}