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