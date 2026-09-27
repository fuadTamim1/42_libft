#include <stdio.h>
#include <string.h>
#include "libft.h"

int main()
{
    char s[] = "abcdefghijklmnvopqstwxyz";
    char d[5];

    // memcpy(d, s, sizeof(char) * 26);
    ft_memcpy(d, s + 3, sizeof(char) * 4);
    d[4] = '\0';
    printf("%s\n", d);
}