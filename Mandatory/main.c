/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:04:00 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/18 21:03:37 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex[1];

	if (ac < 5)
		return (1);
	ft_bzero(pipex, sizeof(pipex));
	pipex->ac = ac;
	pipex->av = av;
	pipex->env = env;
	pipex->prev_in = -1;
	if (!ft_strncmp(av[1], "here_doc", 8))
		ft_here_doc(pipex);
	ft_pipex(pipex, (2 + pipex->here_doc));
	return (pipex->exit_code >> 8);
}
int	ft_file2(t_pipex *pipex)
{
	int		fd;
	int		ac;
	char	**av;

	ac = pipex->ac;
	av = pipex->av;
	if (pipex->here_doc)
		fd = ft_open(av[ac - 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = ft_open(av[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		exit(EXIT_FAILURE);
	return (fd);
}

void	ft_pipex(t_pipex *pipex, int i)
{
	pid_t	pid;

	ft_pipe(pipex);
	pid = ft_fork(pipex);
	if (pid == 0)
	{
		if (i == 2)
			ft_dup2(ft_open(pipex->av[1], O_RDONLY, 0), 0);
		else
			ft_dup2(pipex->prev_in, 0);
		ft_dup2(pipex->pipefd[1], 1);
		close(pipex->pipefd[0]);
		if (i == pipex->ac - 2)
			ft_dup2(ft_file2(pipex), 1);
		ft_check_cmd(pipex->av[i], pipex);
	}
	if (i != 2)
		close(pipex->prev_in);
	pipex->prev_in = dup(pipex->pipefd[0]);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	if (i == (pipex->ac - 2))
	{
		waitpid(pid, &pipex->exit_code, 0);
		while (wait(NULL) != -1)
			;
	}
	else
		ft_pipex(pipex, ++i);
}

// void	ft_pipex(t_pipex *pipex)
// {
// 	int	i;

// 	i = 1 + pipex->here_doc;
// 	while (++i < (pipex->ac - 1))
// 	{
// 		ft_pipe(pipex);
// 		if (ft_fork(pipex) == 0)
// 		{
// 			if (i == 2)
// 				ft_dup2(pipex->file1, 0, pipex);
// 			else
// 				ft_dup2(pipex->prev_in, 0, pipex);
// 			ft_dup2(pipex->pipefd[1], 1, pipex);
// 			close(pipex->pipefd[0]);
// 			if (i == pipex->ac - 2)
// 				ft_dup2(pipex->file2, 1, pipex);
// 			ft_check_cmd(pipex->av[i], pipex);
// 		}
// 		ft_dup(pipex->pipefd[0], pipex);
// 		close(pipex->pipefd[0]);
// 		close(pipex->pipefd[1]);
// 		wait(&pipex->exit_code);
// 	}
// }

void	ft_here_doc(t_pipex *pipex)
{
	char	*here_doc;

	pipex->here_doc = 1;
	ft_pipe(pipex);
	while (1)
	{
		ft_dprintf(STDOUT, "> ");
		here_doc = get_next_line(STDIN);
		if (!ft_strncmp(pipex->av[2], here_doc, ft_strlen(here_doc) - 1)
			|| !here_doc)
		{
			free(here_doc);
			pipex->prev_in = dup(pipex->pipefd[0]);
			close(pipex->pipefd[0]);
			close(pipex->pipefd[1]);
			break ;
		}
		ft_dprintf(pipex->pipefd[1], "%s", here_doc);
		free(here_doc);
	}
}

void	ft_check_cmd(char *arg, t_pipex *pipex)
{
	int		i;

	ft_cmds_parse(arg, pipex);
	if (!access(pipex->cmd[0], F_OK))
		ft_execve(pipex);
	ft_parse_path(pipex);
	i = -1;
	while (pipex->path && pipex->path[++i])
	{
		pipex->path_cmd = ft_strjoin(pipex->path[i], pipex->cmd[0]);
		if (!access(pipex->path_cmd, F_OK))
		{
			ft_clear(pipex->path);
			ft_execve(pipex);
		}
		free(pipex->path_cmd);
	}
	ft_clear(pipex->path);
	ft_clear(pipex->cmd);
	ft_cmd_not_exist(arg, pipex);
}
