/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:38 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/18 03:31:52 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_dup2(int old, int new, t_pipex *pipex)
{
	int	code;

	if (dup2(old, new) < 0)
	{
		code = errno;
		ft_clean_parent(pipex);
		ft_dprintf(STDERR_FILENO, "pipex: dup2(): %s\n", strerror(code));
		exit(EXIT_FAILURE);
	}
	close(old);
}

void	ft_dup(int old, t_pipex *pipex)
{
	int	code;

	pipex->prev_in = dup(old);
	if (pipex->prev_in < 0)
	{
		code = errno;
		ft_clean_parent(pipex);
		ft_dprintf(STDERR_FILENO, "pipex: dup(): %s\n", strerror(code));
		exit(EXIT_FAILURE);
	}
}

void	ft_clean_parent(t_pipex *pipex)
{
	close(pipex->file1);
	close(pipex->file2);
	close(pipex->prev_in);
}
