#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

/**
 * main - creats 5 child processes,
 * from a single parent.
 *
 * Return: always 0.
 */
int main(void)
{
int i;

for (i = 0; i < 5; i++)
{
if (fork() == 0)
{
printf("son pid %d from parent pid %d\n", getpid(), getppid());
}
}
return (0);

}
