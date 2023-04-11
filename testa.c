#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **av, char **envp)
{
	int	i = 1;
		while (av[i])
		{
			printf("%d : %s\n", i, av[i]);
			++i;
		}
}
