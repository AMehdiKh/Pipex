/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 07:05:01 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/18 16:52:45 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


// int	main(int argc, char **av, char **envp)
// {
// 	int code;
// 	int pid = fork();
// 	if (pid == 0)
// 	{
// 		exit(3);
// 	}
// 	wait(&code);
// 	int a = (code >> 8) | 255;
// 	printf("%d", a);
// }
int	main(int argc, char **av, char **envp)
{
	char	*argv[] = {"/usr/bin/awk", "'{print}'", NULL};
	if (execve(argv[0], argv, envp) < 0)
	{
		int code = errno;
		// perror("error");
		printf("%d", code);
	}
	
}
// int	main(int argc, char **av, char **envp)
// {
// 	char	*argv[] = {"/usr/bin/caffeinate", "-s", "-m", NULL};
// 	execve(argv[0], argv, envp);
// }
