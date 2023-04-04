/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mnb3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:04:00 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/04 05:47:30 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex[1];

	ft_bzero(pipex, sizeof(pipex));
	pipex->ac = ac;
	pipex->av = av;
	pipex->env = env;
	pipex->file2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC);
	if (pipex->file2 < 0)
	{
		ft_printf(2, "pipex: %s: %s\n", av[ac - 1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	pipex->file1 = open(av[1], O_RDONLY);
	if (pipex->file1 < 0)
	{
		ft_printf(2, "pipex: %s: %s\n", av[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	ft_path(pipex);
	return (0);
}

int	pipex(t_pipex *pipex)
{
	int	i;

	i = 2;
	while (i < pipex->ac - 1)
	{
		ft_pipe(pipex);
		if (ft_fork(pipex) == 0)
		{
			if (i == 2)
				ft_dup2(pipex->file1, 0);
			else
				ft_dup2(pipex->prev_in, 0);
			ft_dup2(pipex->pipefd[1], 1);
			close(pipex->pipefd[0]);
			if (i == pipex->ac - 2)
				ft_dup2(pipex->file2, 1);
			if (ft_check_cmd(av[i], pipex))
			{
				if (pipex->valid_path)
					pipex->full_cmd = ft_strjoin(pipex->valid_path, av[i]);
				else
					pipex->full_cmd = ft_strdup(av[i]);
				ft_cmds_parse(pipex->full_cmd, pipex);
				ft_execve(pipex);
			}
			exit(EXIT_FAILURE);
		}
		pipex->prev_in = dup(pipefd[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		wait(NULL);
		++i;
	}
	return (0);
}

void	ft_execve(t_pipex *pipex)
{
	if (execve(pipex->cmd[0], pipex->cmd, pipex->env) < 0)
	{
		ft_printf(2, "pipex: %s: %s\n", pipex->cmd[0], strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void	ft_pipe(t_pipex *pipex)
{
	if (pipe(pipefd) < 0)
	{
		ft_printf(2, "pipex: pipe(): %s\n", strerror(errno));
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
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	ft_path(t_pipex *pipex, char **env)
{
	int		i;

	i = 0;
	while (pipex->env[i])
	{
		if (!ft_strncmp("PATH=", pipex->env[i], 5))
		{
			pipex->path = ft_split(&pipex->env[i][5], ':');
			if (!pipex->path)
			{
				ft_printf(2, "pipex: ft_split(): %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			break ;
		}
		++i;
	}
	if (!pipex->path)
	{
		i = 1;
		while (++i < pipex->ac - 1)
			ft_printf(2, "pipex: %s: No such file or directory\n", pipex->av[i]);
		exit(EXIT_FAILURE);
	}
}

void	ft_cmds_parse(char *cmd, t_pipex *pipex)
{
	pipex->cmd = ft_split(cmd, ' ');
	if (!pipex->cmd)
	{
		ft_printf(STDERR_FILENO, "pipex: ft_split(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	free(cmd);
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

void	ft_dup2(int new, int old)
{
	if (dup2(new, old) < 0)
	{
		ft_printf(STDERR_FILENO, "pipex: dup2(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	close(new);
}

int	ft_check_cmd(char *cmd, t_pipex *pipex)
{
	int		i;
	char	*full_cmd;
	char	*path;

	ft_cmd_name(cmd, pipex);
	if (!access(pipex->cmd_name, F_OK) && !access(pipex->cmd_name, X_OK))
	{
		free(pipex->cmd_name);
		return (1);
	}
	i = 0;
	while (pipex->path[i])
	{
		path = ft_strjoin(pipex->path[i], "/");
		full_cmd = ft_strjoin(path, pipex->cmd_name);
		if (!access(full_cmd, F_OK) && !access(full_cmd, X_OK))
		{
			pipex->valid_path = path;
			free(pipex->cmd_name);
			free(full_cmd);
			free(path);
			return (1);
		}
		free(full_cmd);
		free(path);
		++i;
	}
	ft_printf(2, "pipex: %s: %s\n", pipex->cmd_name, strerror(errno));
	free(pipex->cmd_name);
	return (0);
}
