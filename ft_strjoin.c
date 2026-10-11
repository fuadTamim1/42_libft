/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftamimi <ftamimi@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 12:28:44 by ftamimi           #+#    #+#             */
/*   Updated: 2026/10/11 17:26:44 by ftamimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*n;
	size_t			l1;
	size_t			l2;
	unsigned int	i;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	n = malloc((l1 + l2 + 1) * sizeof(char));
	i = 0;
	if (!n)
		return (NULL);
	while (i < l1)
	{
		n[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < l2)
	{
		n[i + l1] = s2[i];
		i++;
	}
	n[l1 + l2] = '\0';
	return (n);
}
