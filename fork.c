/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 07:05:01 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/23 09:26:10 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int	main(int argc, char **av, char **envp)
{
	char* argv[] = {"/bin/ls", "-l", "~/Desktop", NULL};

// 	int pid = fork();
// 	wait(NULL);
// if (pid == 0)
	if (execve("/bin/ls", argv, NULL) == -1)
		perror("Could not execve");
	exit(0);
}
