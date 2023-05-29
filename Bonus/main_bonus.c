/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 01:04:00 by ael-khel          #+#    #+#             */
/*   Updated: 2023/05/29 23:39:07 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex[1];

	if (ac < 5)
		return (EXIT_FAILURE);
	ft_bzero(pipex, sizeof(pipex));
	pipex->ac = ac;
	pipex->av = av;
	pipex->env = env;
	if (!ft_strncmp(av[1], "here_doc", ft_strlen("here_doc") + 1))
		ft_heredoc(pipex);
	ft_pipex(pipex, (2 + pipex->heredoc));
	return (pipex->exit_code >> 8);
}

void	ft_heredoc(t_pipex *pipex)
{
	char	*heredoc;

	pipex->heredoc = 1;
	ft_pipe(pipex);
	while (1)
	{
		ft_dprintf(STDOUT, "> ");
		heredoc = get_next_line(STDIN);
		if (ft_heredoc_cmp(pipex, heredoc))
		{
			free(heredoc);
			ft_close_pipe(pipex, 2);
			break ;
		}
		ft_dprintf(pipex->pipefd[1], "%s", heredoc);
		free(heredoc);
	}
}

void	ft_pipex(t_pipex *pipex, t_shell *shell, t_lexer *lexer)
{
	pid_t	pid;

	ft_pipe(pipex);
	pid = ft_fork(pipex);
	if (pid == 0)
	{
		t_lexer *cmd;
	
		cmd = NULL;
		close(pipex->pipefd[0]);
		ft_dup2(pipex->prev_in, STDIN_FILENO);
		ft_dup2(pipex->pipefd[1], STDOUT_FILENO);
		lexer = ft_redi_parser(lexer);
		if (!lexer)
			exit(EXIT_SUCCESS);
		if (lexer->type == CMD || lexer->type == BUILTIN)
		{
			cmd = lexer;
			lexer += lexer->next;
			lexer = ft_redi_parser(lexer);
		}
		if (cmd)
			ft_check_cmd(cmd->word, pipex);
	}
	ft_close_pipe(pipex);
	lexer = ft_grp_shift(lexer);
	if (lexer)
		ft_pipex(pipex, shell, lexer);
	if (!lexer)
		waitpid(pid, &pipex->exit_code, 0);
	else
		waitpid(pid, NULL, 0);
}

t_lexer	*ft_redi_parser(t_lexer *lexer)
{
	while (lexer && (lexer->type == R_FILE || lexer->type == W_A_FILE || lexer->type == W_T_FILE))
	{
		if (lexer->type == R_FILE)
			ft_dup2(ft_open(lexer->word, O_RDONLY, 0), STDIN_FILENO);
		else if (lexer->type == W_A_FILE || lexer->type == W_T_FILE)
			ft_dup2(ft_file2(lexer), STDOUT_FILENO);
		lexer += lexer->next;
	}
	return (lexer);
}
t_lexer	*ft_grp_shift(t_lexer *lexer)
{
	while (lexer && (lexer->type == R_FILE || lexer->type == W_A_FILE 
		|| lexer->type == W_T_FILE || lexer->type == CMD || lexer->type == BUILTIN))
		lexer += lexer->next;
	if (lexer && lexer->type == PIPE)
		lexer += lexer->next;
	return (lexer);
}

void	ft_check_cmd(char *arg, t_pipex *pipex)
{
	int		i;

	ft_cmds_parse(arg, pipex);
	if (!access(pipex->cmd[0], F_OK))
		ft_execve(pipex);
	ft_parse_path(pipex);
	i = -1;
	while (pipex->path && pipex->path[++i])
	{
		pipex->path_cmd = ft_strjoin(pipex->path[i], pipex->cmd[0]);
		if (!access(pipex->path_cmd, F_OK))
			ft_execve(pipex);
		free(pipex->path_cmd);
	}
	if (pipex->path)
		ft_dprintf(STDERR, "pipex: %s: command not found\n", pipex->cmd[0]);
	else
		ft_dprintf(2, "pipex: %s: No such file or directory\n", pipex->cmd[0]);
	ft_clear(pipex->path);
	ft_clear(pipex->cmd);
	exit(CMD_NOT_FOUND);
}
