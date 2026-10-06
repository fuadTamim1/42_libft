/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftamimi <ftamimi@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 23:48:36 by ftamimi           #+#    #+#             */
/*   Updated: 2026/10/01 23:48:36 by ftamimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*a;

	slen = ft_strlen(s);
	if (start >= slen)
	{
		a = ft_strdup("");
		return (a);
	}
	if (len > slen - start)
		len = slen - start;
	a = ft_calloc(len + 1, sizeof(char));
	if (!a)
		return (NULL);
	ft_strlcpy(a, s + start, len + 1);
	return (a);
}