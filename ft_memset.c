/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftamimi <ftamimi@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 14:30:57 by ftamimi           #+#    #+#             */
/*   Updated: 2026/10/10 14:30:57 by ftamimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*p;
	char	cc;

	p = (char *)s;
	cc = (char)c;
	while (n--)
		*p++ = cc;
	return (s);
}
