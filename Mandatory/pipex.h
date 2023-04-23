/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:29:38 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/23 11:26:46 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	int		ac;
	int		pipefd[2];
	int		prev_in;
	int		exit_code;
	char	**av;
	char	**env;
	char	**cmd;
	char	**path;
	char	*path_cmd;
}		t_pipex;

/* ################ - main.c - ################ */
void	ft_pipex(t_pipex *pipex, int i);
void	ft_check_cmd(char *arg, t_pipex *pipex);

/* ############## - parse_cmd.c - ############## */
void	ft_cmds_parse(char *arg, t_pipex *pipex);
void	ft_parse_path(t_pipex *pipex);
void	ft_slash_end(t_pipex *pipex);
void	ft_close_pipe(t_pipex *pipex, int i);
void	ft_clear(char **ptr);

/* ############### - utils_I.c - ############### */
int		ft_open(const char *pathname, int flags, mode_t mode);
void	ft_pipe(t_pipex *pipex);
pid_t	ft_fork(t_pipex *pipex);
void	ft_dup2(int old, int new);
void	ft_execve(t_pipex *pipex);

#endif