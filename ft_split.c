/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftamimi <ftamimi@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 18:07:42 by ftamimi           #+#    #+#             */
/*   Updated: 2026/10/04 18:07:42 by ftamimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

size_t	word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

void	free_all(char **arr, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	unsigned int i, j, o;
	char *k;
	char **arr;
	size_t n;

	i = 0;
	o = 0;
	n = count_words(s, c);
	arr = ft_calloc(n + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		j = word_len(s + i, c);
		k = ft_substr(s, i, j);
		if (j == 0 || !k)
		{
			free_all(arr, n);
			return (NULL);
		}
		arr[o++] = k;
		i += j;
	}
	arr[n] = NULL;

	return (arr);
}