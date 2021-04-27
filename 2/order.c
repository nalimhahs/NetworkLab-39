#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
	if (fork() == 0)
	{
		sleep(4);
		printf("first child\n");
	}
	else
	{
		if (fork() == 0)
		{
			sleep(2);
			printf("second child\n");
		}
		else
		{
			if (fork() == 0)
			{
				printf("third child\n");
			}
			else
			{
				sleep(6);
				printf("parent process\n");
				exit(0);
			}
		}
	}
}