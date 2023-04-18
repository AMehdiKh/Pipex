/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:06:23 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/18 03:31:52 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_cmds_parse(char *arg, t_pipex *pipex)
{
	pipex->cmd = ft_split(arg, ' ');
	if (!pipex->cmd)
	{
		ft_dprintf(STDERR_FILENO, "pipex: ft_split(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	ft_parse_path(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->env && pipex->env[i])
	{
		if (!ft_strncmp("PATH=", pipex->env[i], 5))
		{
			pipex->path = ft_split(&pipex->env[i][5], ':');
			if (!pipex->path)
			{
				ft_dprintf(2, "pipex: ft_split(): %s\n", strerror(errno));
				free(pipex->cmd_name);
				close(pipex->file1);
				close(pipex->file2);
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

void	ft_cmd_name(char *arg, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (arg[i] != ' ' && arg[i])
		++i;
	pipex->cmd_name = malloc(i + 1);
	if (!pipex->cmd_name)
	{
		ft_dprintf(STDERR_FILENO, "pipex: malloc(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(pipex->cmd_name, arg, (i + 1));
}

void	ft_cmd_not_exist(char *arg, t_pipex *pipex)
{
	ft_cmd_name(arg, pipex);
	if (pipex->path)
		ft_dprintf(2, "pipex: %s: command not found", pipex->cmd_name);
	else
		ft_dprintf(2, "pipex: %s: No such file or directory", pipex->cmd_name);
	free(pipex->cmd_name);
}
