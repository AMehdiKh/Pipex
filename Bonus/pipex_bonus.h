/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:29:38 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/18 10:32:34 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include "../LibFT/include/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define PERM_DENIED 126
# define CMD_NOT_FOUND 127

typedef struct s_pipex
{
	char	**path;
	char	**cmd;
	char	*cmd_name;
	char	*valid_path;
	char	*full_cmd;
	char	**av;
	char	**env;
	int		exit_code;
	int		ac;
	int		pipefd[2];
	int		prev_in;
	int		file1;
	int		file2;
	int		here_doc;
}		t_pipex;

void	ft_pipex(t_pipex *pipex);
void	ft_here_doc(t_pipex *pipex);
void	ft_check_cmd(char *arg, t_pipex *pipex);
void	ft_cmds_parse(char *arg, t_pipex *pipex);
void	ft_parse_path(t_pipex *pipex);
void	ft_slash_end(t_pipex *pipex);
void	ft_cmd_name(char *arg, t_pipex *pipex);
void	ft_cmd_not_exist(char *arg, t_pipex *pipex);
int		ft_open(const char *pathname, int flags, mode_t mode);
void	ft_pipe(t_pipex *pipex);
pid_t	ft_fork(t_pipex *pipex);
void	ft_execve(t_pipex *pipex);
void	ft_clear(char **ptr);
void	ft_dup2(int old, int new, t_pipex *pipex);
void	ft_dup(int old, t_pipex *pipex);
void	ft_clean_parent(t_pipex *pipex);

#endif