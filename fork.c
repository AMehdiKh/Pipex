/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 07:05:01 by ael-khel          #+#    #+#             */
/*   Updated: 2023/03/20 11:43:03 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	int	a, b;

	a = fork();
	b = getpid();
	printf("fork %d pid %d\n", a, b);

	if (a == 0)
	{
		// a = fork();
		b = getppid();
		printf("hadci f 9lb fork %d pid %d\n", a, b);
	}
	if (a != 0)
	{
		sleep(50);
	}
	return (0);
}
