#include "libft.h"

void *ft_calloc(size_t n, size_t c)
{
	void *p;

	if (c == 0)
		return (NULL);
	if (c != 0 && n > (size_t)-1 / c)
		return (NULL);
	p = malloc(n * c);
	if (!p)
		return (NULL);
	ft_bzero(p, n * c);
	return p;
}