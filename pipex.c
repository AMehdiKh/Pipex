/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:04:00 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/11 18:40:26 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "LibFT/libft.h"
#include <string.h>
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex[1];

	ft_bzero(pipex, sizeof(pipex));
	pipex->ac = ac;
	pipex->av = av;
	pipex->env = env;
	pipex->prev_in = -1;
	pipex->file2 = ft_open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	pipex->file1 = ft_open(av[1], O_RDONLY, 0);
	ft_clean_parent(pipex);
	return (0);
}

void	pipex(t_pipex *pipex)
{
	int	i;

	i = 1;
	while (++i < (pipex->ac - 1))
	{
		ft_pipe(pipex);
		if (ft_fork(pipex) == 0)
		{
			if (i == 2)
				ft_dup2(pipex->file1, 0, pipex);
			else
				ft_dup2(pipex->prev_in, 0, pipex);
			ft_dup2(pipex->pipefd[1], 1, pipex);
			close(pipex->pipefd[0]);
			if (i == pipex->ac - 2)
				ft_dup2(pipex->file2, 1, pipex);
			ft_check_cmd(pipex->av[i], pipex);
			exit(127);
		}
		ft_dup(pipefd[0], pipex);
		close(pipefd[0]);
		close(pipefd[1]);
		wait(NULL);
	}
}

void	ft_parse_path(t_pipex *pipex, char **env)
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
				ft_printf(2, "pipex: ft_split(): %s\n", strerror(errno));
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

void	ft_cmds_parse(char *cmd, t_pipex *pipex)
{
	int	i;
	if (ft_strchr(cmd, 39) || ft_strchr(cmd, 34))
	{
		pipex->cmd = ft_split(cmd, ' ');
		free(cmd);
	}
	else
	{
		pipex->cmd = ft_split(cmd, ' ');
		free(cmd);
		if (!pipex->cmd)
		{
			ft_printf(STDERR_FILENO, "pipex: ft_split(): %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_cmd_name(char *cmd, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (cmd[i] != ' ' && cmd[i])
		++i;
	pipex->cmd_name = malloc(i + 1);
	if (!pipex->cmd_name)
	{
		ft_printf(STDERR_FILENO, "pipex: malloc(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(pipex->cmd_name, cmd, (i + 1));
}

int	ft_check_cmd(char *cmd, t_pipex *pipex)
{
	char	*path_cmd_name;
	int		i;

	ft_cmd_name(cmd, pipex);
	if (!access(pipex->cmd_name, F_OK))
	{
		free(pipex->cmd_name);
		ft_cmds_parse(ft_strdup(cmd), pipex);
		ft_execve(pipex);
	}
	i = 0;
	ft_parse_path(pipex);
	while (pipex->path && pipex->path[i])
	{
		path_cmd_name = ft_strjoin(pipex->path[i], pipex->cmd_name);
		if (!access(path_cmd_name, F_OK))
		{
			free(pipex->cmd_name);
			free(path_cmd_name);
			ft_clear(pipex->path);
			ft_cmds_parse(ft_strjoin(pipex->path[i], cmd), pipex);
			ft_execve(pipex);
		}
		free(path_cmd_name);
		++i;
	}
	if (pipex->path)
		ft_printf(2, "pipex: %s: command not found", pipex->cmd_name);
	else
		ft_printf(2, "pipex: %s: %s", pipex->cmd_name, strerror(errno));
	free(pipex->cmd_name);
	ft_clear(pipex->path);
	return (0);
}
