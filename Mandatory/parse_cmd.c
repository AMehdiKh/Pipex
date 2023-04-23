/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:06:23 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/23 11:23:51 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmds_parse(char *arg, t_pipex *pipex)
{
	int	code;

	pipex->cmd = ft_split(arg, ' ');
	if (!pipex->cmd)
	{
		code = errno;
		ft_dprintf(STDERR, "pipex: ft_split(): %s\n", strerror(code));
		exit(EXIT_FAILURE);
	}
}

void	ft_parse_path(t_pipex *pipex)
{
	int	code;
	int	i;

	i = 0;
	while (pipex->env && pipex->env[i])
	{
		if (!ft_strncmp("PATH=", pipex->env[i], 5))
		{
			pipex->path = ft_split(&pipex->env[i][5], ':');
			if (!pipex->path)
			{
				code = errno;
				ft_clear(pipex->cmd);
				ft_dprintf(STDERR, "pipex: ft_split(): %s\n", strerror(code));
				exit(EXIT_FAILURE);
			}
			break ;
		}
		++i;
	}
	ft_slash_end(pipex);
}

void	ft_slash_end(t_pipex *pipex)
{
	char	*path;
	int		i;

	if (pipex->path)
	{
		i = 0;
		while (pipex->path[i])
		{
			path = ft_strjoin(pipex->path[i], "/");
			free(pipex->path[i]);
			pipex->path[i] = path;
			++i;
		}
	}
}

void	ft_close_pipe(t_pipex *pipex, int i)
{
	if (i != 2)
		close(pipex->prev_in);
	pipex->prev_in = dup(pipex->pipefd[0]);
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
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
