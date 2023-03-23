/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:28:39 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/23 08:02:10 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex[1];
	int		pipe_fd[2];

	if (ac != 5)
		return (0);
	if (pipe(pipe_fd) == -1)
	{
		ft_printf(STDERR_FILENO, "pipex: %s: %s\n", "pipe()", strerror(errno));
		exit(EXIT_FAILURE);
	}
	pipex->av = av;
	pipex->env = env;
	pipex->pipe_in = pipe_fd[0];
	pipex->pipe_out = pipe_fd[1];
	pipex->file1 = open(av[1], O_RDONLY);
	if (pipex->file1 < 0)
	{
		ft_printf(STDERR_FILENO, "pipex: %s: %s\n", av[1], strerror(errno));
	}
	ft_dup2(pipex->file1, 0);
	ft_dup2(pipex->pipe_out, 1);
	int i = 2;
	while (av[i])
	{
		if (i == 3)
		{
			ft_dup2(pipex->pipe_in, pipex->file1);
		}
		if (!av[i + 1])
		{
			ft_dup2(pipex->file2, pipex->pipe_out);
		}
		if (ft_check_cmd())
	}
	return (0);
}

void	ft_path(t_pipex *pipex, char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			path = ft_split(&env[i][5], ':');
			if (!path)
			{
				ft_printf(STDERR_FILENO,
					"pipex: ft_split(): %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			break ;
		}
		++i;
	}
	return (path);
}

char	**ft_cmds_parse(char *cmd, t_pipex *pipex)
{
	pipex->cmd = ft_split(cmd, ' ');
	if (!pipex->cmd)
	{
		ft_printf(STDERR_FILENO, "pipex: ft_split(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

char	*ft_cmd_name(char *cmd, t_pipex *pipex)
{
	char	*cmd_name;
	int		i;

	i = 0;
	while (cmd[i] != ' ')
		++i;
	cmd_name = malloc(i + 1);
	if (!cmd_name)
	{
		ft_printf(STDERR_FILENO, "pipex: malloc(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(cmd_name, cmd, (i + 1));
	return (cmd_name);
}

int	ft_dup2(int new, int old)
{
	int	fd;

	fd = dup2(new, old);
	if (fd < 0)
	{
		ft_printf(STDERR_FILENO, "pipex: dup2(): %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	close(old);
	return (fd);
}
