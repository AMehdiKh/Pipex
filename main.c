/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:28:39 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/17 18:10:21 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		in_fd;
	int		out_fd;
	char	*error;

	if (ac != 5)
		return (0);
	in_fd = open(av[1], O_RDONLY);
	if (in_fd < 0)
		ft_printf(STDERR_FILENO, "bash: %s: %s\n", av[1], strerror(errno));
	char* argv[] = {"ls", "-la", NULL };
  	char* envp[] = { "/bin/", NULL};
  	if (execve("/bin/ls", argv, NULL) == -1)
		perror("Could not execve");
	return (0);
}
