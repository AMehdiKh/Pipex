/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_II_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 03:03:38 by ael-khel          #+#    #+#             */
/*   Updated: 2023/05/29 23:14:32 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_heredoc_cmp(t_pipex *pipex, char *heredoc)
{
	size_t	i;

	if (!heredoc)
		return (1);
	if (!*pipex->av[2] && *heredoc == '\n')
		return (1);
	if (ft_strlen(pipex->av[2]) != ft_strlen(heredoc) - 1)
		return (0);
	i = 0;
	while (pipex->av[2][i])
	{
		if (pipex->av[2][i] != heredoc[i])
			return (0);
		++i;
	}
	return (1);
}

int	ft_file2(t_lexer *lexer)
{
	int		fd;

	if (lexer->node->type == W_A_FILE)
		fd = ft_open(lexer->node->word, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (lexer->node->type == W_T_FILE)
		fd = ft_open(lexer->node->word, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	return (fd);
}

void	ft_close_pipe(t_pipex *pipex)
{
	if (pipex->prev_in)
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
