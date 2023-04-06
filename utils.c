/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 17:51:43 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/05 18:36:05 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

void	ft_clean_parent(t_pipex *pipex)
{
	close(pipex->file1);
	close(pipex->file2);
	close(pipex->prev_in);
}

int	ft_open(const char *pathname, int flags, mode_t mode)
{
	int	fd;

	fd = open(pathname, flags, mode);
	if (fd < 0)
	{
		ft_printf(2, "pipex: %s: %s\n", pathname, strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	ft_execve(t_pipex *pipex)
{
	if (execve(pipex->cmd[0], pipex->cmd, pipex->env) < 0)
	{
		ft_printf(2, "pipex: %s: %s\n", pipex->cmd[0], strerror(errno));
		ft_clear(pipex->cmd);
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

void	ft_pipe(t_pipex *pipex)
{
	if (pipe(pipex->pipefd) < 0)
	{
		ft_printf(2, "pipex: pipe(): %s\n", strerror(errno));
		ft_clean_parent(pipex);
		exit(EXIT_FAILURE);
	}
}

pid_t	ft_fork(t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_printf(2, "pipex: fork(): %s\n", strerror(errno));
		ft_clean_parent(pipex);
		close(pipex->pipefd[0]);
		close(pipex->pipefd[1]);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	ft_dup2(int old, int new, t_pipex *pipex)
{
	if (dup2(old, new) < 0)
	{
		ft_printf(STDERR_FILENO, "pipex: dup2(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	close(old);
}

void	ft_dup(int old, t_pipex *pipex)
{
	pipex->prev_in = dup(old);
	if (pipex->prev_in < 0)
	{
		ft_printf(STDERR_FILENO, "pipex: dup(): %s\n", strerror(errno));
		ft_clean_parent(pipex);
		exit(EXIT_FAILURE);
	}
}
