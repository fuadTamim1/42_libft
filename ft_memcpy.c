/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftamimi <ftamimi@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 15:24:50 by ftamimi           #+#    #+#             */
/*   Updated: 2026/09/27 15:24:50 by ftamimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (!dest || !src)
		return (dest);
	d = (char *)dest;
	s = (const char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}
