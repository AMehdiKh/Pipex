/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 07:05:01 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/22 20:53:21 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


// int	main(int argc, char **av, char **envp)
// {
// 	int code;
// 	int pid = fork();
// 	if (pid == 0)
// 	{
// 		exit(3);
// 	}
// 	wait(&code);
// 	int a = (code >> 8) | 255;
// 	printf("%d", a);
// }

// void	ft_pipex(t_pipex *pipex)
// {
// 	int	i;

// 	i = 1 + pipex->heredoc;
// 	while (++i < (pipex->ac - 1))
// 	{
// 		ft_pipe(pipex);
// 		if (ft_fork(pipex) == 0)
// 		{
// 			if (i == 2)
// 				ft_dup2(pipex->file1, 0, pipex);
// 			else
// 				ft_dup2(pipex->prev_in, 0, pipex);
// 			ft_dup2(pipex->pipefd[1], 1, pipex);
// 			close(pipex->pipefd[0]);
// 			if (i == pipex->ac - 2)
// 				ft_dup2(pipex->file2, 1, pipex);
// 			ft_check_cmd(pipex->av[i], pipex);
// 		}
// 		ft_dup(pipex->pipefd[0], pipex);
// 		close(pipex->pipefd[0]);
// 		close(pipex->pipefd[1]);
// 		wait(&pipex->exit_code);
// 	}
// }

int	main(int argc, char **av, char **envp)
{
	if (fork() == 0)
		while(1);
	while(1);
	// char	*argv[] = {"awk", "'{print}'", NULL};
	// if (execve("/usr/bin/awk", argv, envp) < 0)
	// {
	// 	int code = errno;
	// 	// perror("error");
	// 	printf("%d", code);
	// }
}
// int	main(int argc, char **av, char **envp)
// {
// 	char	*argv[] = {"/usr/bin/caffeinate", "-s", "-m", NULL};
// 	execve(argv[0], argv, envp);
// }
