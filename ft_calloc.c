/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftamimi <ftamimi@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 16:01:52 by ftamimi           #+#    #+#             */
/*   Updated: 2026/10/11 01:02:19 by ftamimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t c)
{
	void	*p;

	if (c != 0 && n > (size_t)-1 / c)
		return (NULL);
	p = malloc(n * c);
	if (!p)
		return (NULL);
	ft_bzero(p, n * c);
	return (p);
}
