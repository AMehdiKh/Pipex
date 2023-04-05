/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:04:00 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/05 02:28:26 by ael-khel         ###   ########.fr       */
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
	ft_parse_path(pipex);
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
				ft_dup2(pipex->file1, 0);
			else
				ft_dup2(pipex->prev_in, 0);
			ft_dup2(pipex->pipefd[1], 1);
			close(pipex->pipefd[0]);
			if (i == pipex->ac - 2)
				ft_dup2(pipex->file2, 1);
			ft_check_cmd(pipex->av[i], pipex);
			exit(EXIT_FAILURE);
		}
		ft_dup(pipefd[0], pipex);
		close(pipefd[0]);
		close(pipefd[1]);
		wait(NULL);
	}
}
void	ft_clean_parent(t_pipex *pipex)
{
	ft_clear(pipex->path);
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
		exit(EXIT_FAILURE);
	}
	return (pid);
}
void	ft_dup2(int old, int new)
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

void	ft_parse_path(t_pipex *pipex, char **env)
{
	int	i;

	i = 0;
	while (pipex->env[i] && pipex->env[i])
	{
		if (!ft_strncmp("PATH=", pipex->env[i], 5))
		{
			pipex->path = ft_split(&pipex->env[i][5], ':');
			if (!pipex->path)
			{
				ft_printf(2, "pipex: ft_split(): %s\n", strerror(errno));
				close(pipex->file1);
				close(pipex->file2);
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
	free(cmd);
	if (!pipex->cmd)
	{
		ft_printf(STDERR_FILENO, "pipex: ft_split(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
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
	char	*full_cmd;
	char	*path;
	int		i;

	ft_cmd_name(cmd, pipex);
	if (!access(pipex->cmd_name, F_OK))
	{
		free(pipex->cmd_name);
		ft_cmds_parse(ft_strdup(cmd), pipex);
		ft_execve(pipex);
	}
	i = 0;
	while (pipex->path && pipex->path[i])
	{
		path = ft_strjoin(pipex->path[i], "/");
		full_cmd = ft_strjoin(path, pipex->cmd_name);
		if (!access(full_cmd, F_OK))
		{
			free(pipex->cmd_name);
			free(full_cmd);
			ft_cmds_parse(ft_strjoin(path, cmd), pipex);
			free(path);
			ft_execve(pipex);
		}
		free(full_cmd);
		free(path);
		++i;
	}
	if (pipex->path)
		ft_printf(2, "pipex: %s: command not found", pipex->cmd_name);
	else
		ft_printf(2, "pipex: %s: %s", pipex->cmd_name, strerror(errno));
	free(pipex->cmd_name);
	return (0);
}
