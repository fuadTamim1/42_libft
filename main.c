#include <stdio.h>
#include <string.h>
#include "libft.h"

int main()
{
    char s[10];

    // memcpy(d, s, sizeof(char) * 26);
    // ft_memcpy(d, s + 3, sizeof(char) * 4);
    // d[4] = '\0';

    // memset(s, 'c', sizeof(char) * 5);
    // memset(s+5, 'd', sizeof(char) * 5);
    // ft_memset(s, 'c', sizeof(char) * 5);
    // ft_memset(s+5, 'd', sizeof(char) * 5);
    
    int *a;
    a = ft_calloc(10, sizeof(int));    
    for (int i = 0; i < 10; i++)
    {
        printf("%d", a[i]);
    }
    
}