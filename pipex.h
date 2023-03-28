/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:29:38 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/23 10:13:26 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "/Users/ael-khel/Desktop/Pipex/LibFT/libft.h"

typedef struct s_pipex
{
	char	**path;
	char	**cmd;
	char	**av;
	char	**env;
	char	*cmd_name;
	char	*valid_path;
	int		pipe_in;
	int		pipe_out;
	int		file1;
	int		file2;
}		t_pipex;

void	ft_path(t_pipex *pipex, char **env);
void	ft_cmds_parse(char *cmd, t_pipex *pipex);
void	ft_cmd_name(char *cmd, t_pipex *pipex);
int		ft_dup2(int new, int old);
int		ft_check_cmd(char *cmd, t_pipex *pipex);


#endif