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

static int	ft_end_quoted(const char **s, int *quote)
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
	else
		*quote = 0;
	return (0);
}

static size_t	ft_word_len(const char **s, size_t wl, int *e_quote, char c)
{
	int	quote;

	*e_quote = ft_end_quoted(s, &quote);
	*s -= (quote && !*e_quote);
	wl += (quote && !*e_quote);
	while (*(*s + wl))
	{
		if ((*e_quote && *(*s + wl) == quote && (*(*s + (wl + 1)) == ' '
					|| *(*s + (wl + 1)) == '\0'))
			|| (!*e_quote && *(*s + wl) == c))
			break ;
		++wl;
	}
	return (wl);
}

static char	**ft_insert(char **ptr, const char *s, char c, size_t wc)
{
	size_t	wl;
	size_t	x;
	int		e_quote;

	x = 0;
	while (*s && x < wc)
	{
		wl = 0;
		while (*s == c && *s)
			++s;
		wl = ft_word_len(&s, wl, &e_quote, c);
		ptr[x] = malloc(wl + 1);
		if (!ptr[x])
			return (ft_clear_split(ptr, x));
		ft_strlcpy(ptr[x], s, wl + 1);
		s += (wl + e_quote);
		++x;
	}
	return (ptr);
}

static size_t	ft_word_count(const char *s, char c)
{
	int		e_quote;
	int		quote;
	size_t	wc;

	wc = 0;
	while (*s)
	{
		while (*s == c && *s)
			++s;
		if (*s)
			++wc;
		e_quote = ft_end_quoted(&s, &quote);
		while (*s)
		{
			if ((e_quote && *s == quote && (*(s + 1) == ' '
						|| *(s + 1) == '\0')) || (!e_quote && *s == c))
			{
				s += e_quote;
				break ;
			}
			++s;
		}
	}
	return (wc);
}

char	**ft_split(char const *s, char c)
{
	size_t	wc;
	char	**ptr;

	if (!s)
		return (NULL);
	wc = ft_word_count(s, c);
	ptr = ft_calloc(wc + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	return (ft_insert(ptr, s, c, wc));
}
