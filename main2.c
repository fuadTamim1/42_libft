#include "libft.h"
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	size_t c;
	c = count_words("hello world hi", ' ');
	printf("%d", c);
	return (0);
}