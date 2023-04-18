/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:01:16 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/29 22:01:50 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int	pid;
	int	pip[2];
	int	pop[2];
	int	pxp[2];
	int	file1;
	int	file2;

	file1 = open("in", O_RDONLY);
	file2 = open("out", O_RDWR);
	pipe(pip);
	pipe(pop);
	pipe(pxp);
	pid = fork();
	if (pid == 0)
	{
		dup2(file1, 0);
		close(file1);
		close(file2);
		dup2(pip[1], 1);
		close(pip[1]);
		close(pip[0]);
		char* argv[] = {"/usr/bin/grep", "pipe", NULL};
		execve("/usr/bin/grep", argv, env);
	}
	close(pip[1]);
	wait(NULL);
	pid = fork();
	if (pid == 0)
	{
		dup2(pip[0], 0);
		close(pip[0]);
		dup2(pop[1], 1);
		close(pop[1]);
		close(pop[0]);
		char* argv[] = {"/usr/bin/wc", NULL};
		execve("/usr/bin/wc", argv, env);
	}
	close(pop[1]);
	wait(NULL);
	pid = fork();
	if (pid == 0)
	{
		dup2(pop[0], 0);
		close(pop[0]);
		dup2(pxp[1], 1);
		close(pxp[1]);
		close(pxp[0]);
		char* argv[] = {"/usr/bin/wc", NULL};
		execve("/usr/bin/wc", argv, env);
	}
	close(pxp[1]);
	wait(NULL);
	pid = fork();
	if (pid == 0)
	{
		dup2(pxp[0], 0);
		close(pxp[0]);
		close(pxp[1]);
		dup2(file2, 1);
		close(file2);
		char* argv[] = {"/usr/bin/wc", NULL};
		execve("/usr/bin/wc", argv, env);
	}
	close(pip[0]);
	close(pip[1]);
	close(pop[0]);
	close(pop[1]);
	wait(NULL);
	return (0);
}
