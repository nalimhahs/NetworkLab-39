#include <stdio.h>
#include <unistd.h>

int fact(int x)
{
	if (x > 0)
		return (x * fact(x - 1));
	else
		return 1;
}

void main()
{
	int n;
	printf("Enter the value of n: ");
	scanf("%d", &n);
	if (fork() == 0)
	{
		for (int i = 1; i <= n; i++)
		{
			printf("%d\n", fact(i));
		}
	}
}