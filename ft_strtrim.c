/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftamimi <ftamimi@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 17:21:43 by ftamimi           #+#    #+#             */
/*   Updated: 2026/10/04 17:21:43 by ftamimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int i;
	char *s;
	size_t slen;

	slen = ft_strlen(s1);
	i = 0;
	while (i < slen && ft_strchr(set, s1[i]))
	{
		i++;
	}
	while (i < slen - 1 && ft_strchr(set, s1[slen - 1]))
	{
		slen--;
	}

	s = ft_substr(s1, i, slen - i);
	return (s);
}