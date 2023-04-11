/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 07:05:01 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/11 18:37:59 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(int argc, char **av, char **envp)
{
	char	*argv[] = {"/usr/bin/caffeinate", "-s", "-m", NULL};
	execve(argv[0], argv, envp);
}
