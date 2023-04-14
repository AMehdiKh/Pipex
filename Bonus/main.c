/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:04:00 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/14 03:08:11 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pipex(pipex);
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

void	ft_check_cmd(char *arg, t_pipex *pipex)
{
	char	*path_cmd;
	int		i;

	ft_cmds_parse(arg, pipex);
	if (!access(pipex->cmd[0], F_OK))
		ft_execve(pipex);
	ft_parse_path(pipex);
	i = -1;
	while (pipex->path && pipex->path[++i])
	{
		path_cmd = ft_strjoin(pipex->path[i], pipex->cmd[0]);
		if (!access(path_cmd, F_OK))
		{
			ft_clear(pipex->path);
			free(pipex->cmd[0]);
			pipex->cmd[0] = path;
			ft_execve(pipex);
		}
		free(path_cmd);
	}
	ft_clear(pipex->path);
	ft_clear(pipex->cmd);
	ft_cmd_not_exist(arg, pipex);
}
