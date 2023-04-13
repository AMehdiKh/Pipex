/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 21:48:06 by ael-khel          #+#    #+#             */
/*   Updated: 2023/04/13 06:14:26 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	main(int ac, char **av)
{
	printf("%zu\n", word_count(av[1], ' '));
	// printf("%c\n", str[-1]);
	// char **split = word_count(av[1], ' ');
	// int	i;
	// i = 0;
	// while (split[i])
	// {
	// 	++i;
	// }
	return (0);
}
