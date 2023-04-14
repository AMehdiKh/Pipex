/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:48:06 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/14 00:14:26 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	main(int ac, char **av)
{
	printf ("%s\n", av[1]);
	printf("%zu\n", word_count(av[1], ' '));

	char **split = ft_split(av[1], ' ');
	int	i;
	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		++i;
	}
	return (0);
}
