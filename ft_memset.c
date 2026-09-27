#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*p;
	char cc;

	p = (char *)s;
	cc = (char) c;
	while (n--)
		*p++ = cc;
	return (s);
}
