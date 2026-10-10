/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftamimi <ftamimi@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 01:04:12 by ftamimi           #+#    #+#             */
/*   Updated: 2026/10/10 01:04:12 by ftamimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_len(long long nb)
{
	long long	len;

	len = 0;
	if (nb <= 0)
		len = 1;
	while (nb != 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long long	nb;
	long long	len;
	char		*str;

	nb = n;
	len = count_len(nb);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		str[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (str);
}
