/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 11:03:05 by ael-khel          #+#    #+#             */
/*   Updated: 2022/10/15 11:03:05 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_clear_split(char **ptr, size_t x)
{
	while (x--)
		free(ptr[x]);
	free(ptr);
	return (NULL);
}

// size_t	word_count(char const *s, char c)
// {
// 	size_t	wc;

// 	wc = 0;
// 	while (*s)
// 	{
// 		while (*s == c && *s)
// 			++s;
// 		if (*s)
// 			++wc;
// 		while (*s != c && *s)
// 			++s;
// 	}
// 	return (wc);
// }

char	**ft_alloc(char **ptr, const char *s, char c, size_t wc)
{
	size_t	wl;
	size_t	x;
	int		quote;

	x = 0;
	while (*s && x < wc)
	{
		wl = 0;
		while (*s == c && *s)
			++s;
		if (*s == 39 || *s == 34)
			quote = *s++;
		else
			quote = 0;
		while (s[wl])
		{
			if ((s[wl] == quote && (s[wl + 1] == ' ' || s[wl + 1] == '\0')) || (!quote && s[wl] == c))
				break ;
			++wl;
		}
		ptr[x] = malloc(wl + 1);
		if (!ptr[x])
			return (ft_clear_split(ptr, x));
		ft_strlcpy(ptr[x], s, wl + 1);
		s += wl;
		++x;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	size_t	wc;
	char	**ptr;

	if (!s)
		return (NULL);
	wc = word_count(s, c);
	ptr = ft_calloc(wc + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	return (ft_alloc(ptr, s, c, wc));
}

size_t	word_count(const char *s, char c)
{
	int		quote;
	int		v_quotes;
	size_t	wc;

	wc = 0;
	while (*s)
	{
		while (*s == c && *s)
			++s;
		if (*s)
			++wc;
		v_quotes = ft_end_quoted(&s, &quote);
		while (*s)
		{
			if ((v_quotes && *s == quote && (*(s + 1) == ' '
						|| *(s + 1) == '\0')) || (!v_quotes && *s == c))
			{
				s += v_quotes;
				break ;
			}
			++s;
		}
	}
	return (wc);
}

int	ft_end_quoted(const char **s, int *quote)
{
	int	i;

	i = 0;
	if (**s == 39 || **s == 34)
	{
		*quote = **s;
		*s += 1;
		while (*(*s + i))
		{
			if (*(*s + i) == *quote && (*(*s + (i + 1)) == ' '
					|| *(*s + (i + 1)) == '\0'))
				return (1);
			else if (*(*s + i) == ' ' && *(*s + (i - 1)) != *quote
				&& *(*s + (i + 1)) == *quote
				&& (*(*s + (i + 2)) != '\0' && *(*s + (i + 2)) != ' '))
				return (0);
			++i;
		}
	}
	return (0);
}
