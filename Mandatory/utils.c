/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:51:43 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/18 17:44:49 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	ft_open(const char *pathname, int flags, mode_t mode)
{
	int	fd;
	int	code;

	fd = open(pathname, flags, mode);
	if (fd < 0)
	{
		code = errno;
		ft_dprintf(STDERR, "pipex: %s: %s\n", pathname, strerror(code));
		// exit(1);
	}
	return (fd);
}

void	ft_pipe(t_pipex *pipex)
{
	int	code;

	if (pipe(pipex->pipefd) < 0)
	{
		code = errno;
		ft_clean_parent(pipex);
		ft_dprintf(STDERR, "pipex: pipe(): %s\n", strerror(code));
		exit(EXIT_FAILURE);
	}
}

pid_t	ft_fork(t_pipex *pipex)
{
	pid_t	pid;
	int		code;

	pid = fork();
	if (pid < 0)
	{
		code = errno;
		ft_clean_parent(pipex);
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		ft_dprintf(STDERR, "pipex: fork(): %s\n", strerror(code));
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	ft_execve(t_pipex *pipex)
{
	int	code;

	if (execve(pipex->cmd[0], pipex->cmd, pipex->env) < 0)
	{
		code = errno;
		ft_dprintf(STDERR, "pipex: %s: %s\n", pipex->cmd[0], strerror(code));
		ft_clear(pipex->cmd);
		if (code == EACCES)
			exit(PERM_DENIED);
		exit(EXIT_FAILURE);
	}
}

void	ft_clear(char **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
			free(ptr[i++]);
		free(ptr);
	}
}
