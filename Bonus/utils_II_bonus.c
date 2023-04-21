/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:38 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/20 22:46:19 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
