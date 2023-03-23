/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:29:38 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/23 07:34:38 by ael-khel         ###   ########.fr       */
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

typedef struct s_pipex
{
	char	**path;
	char	**cmd;
	char	**av;
	char	**env;
	int		pipe_in;
	int		pipe_out;
	int		file1;
	int		file2;
}	t_pipex;

#endif