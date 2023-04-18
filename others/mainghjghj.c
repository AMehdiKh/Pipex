/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainghjghj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 19:53:01 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/18 03:31:52 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex[1];

	ft_bzero(pipex, sizeof(pipex));

	int prev = 0;
	int pipefd[2];
	pipex->av = av;
	pipex->env = env;
	pipex->file1 = open(av[1], O_RDONLY);
	if (pipex->file1 < 0)
	{
		ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", av[1], strerror(errno));
	}
	pipex->file2 = open(av[ac - 1], O_WRONLY | O_TRUNC);
	if (pipex->file2 < 0)
	{
		ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", av[1], strerror(errno));
	}
	ft_path(pipex, env);
	int i = 2;
	while (av[i + 1])
	{
		pipe(pipefd);
		int	pid = fork();
		if (pid == 0)
		{
			if (i == 2)
			{
				ft_dup2(pipex->file1, 0);
				ft_dup2(pipefd[1], 1);
				close(pipefd[0]);
			}
			else
			{
				ft_dup2(prev, 0);
				if (!av[i + 2])
					dup2(pipex->file2, 1);
				else
				{
					ft_dup2(pipefd[1], 1);
					close(pipefd[0]);
				}
			}
			if (ft_check_cmd(av[i], pipex))
			{
				char *full_cmd;
				full_cmd = ft_strjoin(ft_strjoin(pipex->valid_path, "/"), av[i]);
				ft_cmds_parse(full_cmd, pipex);
				free(full_cmd);
				ft_dprintf(2, "%s\n", pipex->cmd[0]);
				execve(pipex->cmd[0], pipex->cmd, pipex->env);
			}
		}
		prev = dup(pipefd[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		wait(NULL);
		++i;
	}
	return (0);
}

void	ft_path(t_pipex *pipex, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			pipex->path = ft_split(&env[i][5], ':');
			if (!pipex->path)
			{
				ft_dprintf(STDERR_FILENO,
					"pipex: ft_split(): %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			break ;
		}
		++i;
	}
}

void	ft_cmds_parse(char *cmd, t_pipex *pipex)
{
	pipex->cmd = ft_split(cmd, ' ');
	if (!pipex->cmd)
	{
		ft_dprintf(STDERR_FILENO, "pipex: ft_split(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	ft_cmd_name(char *cmd, t_pipex *pipex)
{
	int		i;

	i = 0;
	while (cmd[i] != ' ')
		++i;
	pipex->cmd_name = malloc(i + 1);
	if (!pipex->cmd_name)
	{
		ft_dprintf(STDERR_FILENO, "pipex: malloc(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(pipex->cmd_name, cmd, (i + 1));
}

int	ft_dup2(int new, int old)
{
	int	fd;

	fd = dup2(new, old);
	if (fd < 0)
	{
		ft_dprintf(STDERR_FILENO, "pipex: dup2(): %s\n", strerror(errno));
		// exit(EXIT_FAILURE);
	}
	close(new);
	return (fd);
}

int	ft_check_cmd(char *cmd, t_pipex *pipex)
{
	int		i;
	char	*full_cmd;

	ft_cmd_name(cmd, pipex);
	i = 0;
	while (pipex->path[i])
	{
		full_cmd = ft_strjoin(ft_strjoin(pipex->path[i], "/"), pipex->cmd_name);
		if (!access(full_cmd, F_OK))
		{
			if (!access(full_cmd, X_OK))
			{
				pipex->valid_path = pipex->path[i];
				free (full_cmd);
				free (pipex->cmd_name);
				return (1);
			}
			break ;
		}
		++i;
	}
	//errno
	return (0);
}
