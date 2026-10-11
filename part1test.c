/* ************************************************************************** */
/*  libft PART 1 tester (libc functions)  -  do NOT push to your repo         */
/*                                                                            */
/*  Build from your libft folder (after make):                                */
/*    cc -Wall -Wextra -Werror -g -fsanitize=address part1test.c libft.a \   */
/*       -I. -o p1 && ./p1                                                    */
/*                                                                            */
/*  Every function is compared against the real libc function.               */
/*  strlcpy / strlcat / strnstr are BSD functions that older Linux libc      */
/*  doesn't have, so this file has its own reference versions of them.       */
/*                                                                            */
/*  Set a switch to 0 to skip a function (it then doesn't need to exist).    */
/*  Add a case: copy a CHECK line inside that function's block.              */
/* ************************************************************************** */

#define T_ISALPHA	1
#define T_ISDIGIT	1
#define T_ISALNUM	1
#define T_ISASCII	1
#define T_ISPRINT	1
#define T_TOUPPER	1
#define T_TOLOWER	1
#define T_STRLEN	1
#define T_MEMSET	1
#define T_BZERO		1
#define T_MEMCPY	1
#define T_MEMMOVE	1
#define T_STRLCPY	1
#define T_STRLCAT	1
#define T_STRCHR	1
#define T_STRRCHR	1
#define T_STRNCMP	1
#define T_MEMCHR	1
#define T_MEMCMP	1
#define T_STRNSTR	1
#define T_ATOI		1
#define T_CALLOC	1
#define T_STRDUP	1

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>

/* ========================================================================== */
/*  Helpers                                                                   */
/* ========================================================================== */

int	g_pass = 0;
int	g_fail = 0;

void	CHECK(const char *name, int ok)
{
	if (ok)
	{
		g_pass++;
		printf("  [OK]   %s\n", name);
	}
	else
	{
		g_fail++;
		printf("  [FAIL] %s\n", name);
	}
}

/* CHECK with the two values printed on failure (for ints / sizes) */
void	CHECK_INT(const char *name, long got, long exp)
{
	if (got == exp)
	{
		g_pass++;
		printf("  [OK]   %s\n", name);
	}
	else
	{
		g_fail++;
		printf("  [FAIL] %s\n         got: %ld\n         exp: %ld\n",
			name, got, exp);
	}
}

/* -1, 0 or 1: comparison functions only promise the sign */
int	sign(long x)
{
	return ((x > 0) - (x < 0));
}

/* reference BSD versions, used as the expected result */
size_t	ref_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	slen;
	size_t	n;

	slen = strlen(src);
	if (size > 0)
	{
		n = slen < size - 1 ? slen : size - 1;
		memcpy(dst, src, n);
		dst[n] = '\0';
	}
	return (slen);
}

size_t	ref_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;

	dlen = 0;
	while (dlen < size && dst[dlen])
		dlen++;
	if (dlen == size)
		return (size + strlen(src));
	return (dlen + ref_strlcpy(dst + dlen, src, size - dlen));
}

char	*ref_strnstr(const char *big, const char *little, size_t len)
{
	size_t	l;
	size_t	i;

	l = strlen(little);
	if (l == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && i + l <= len)
	{
		if (strncmp(big + i, little, l) == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

/* the character range the is/to functions must handle: EOF and 0..255 */
#define CHAR_LOOP(var) for (var = -1; var <= 255; var++)

/* ========================================================================== */
/*  Character functions: every value from EOF to 255                          */
/*  (they only promise zero / non-zero, so results are compared as bools)     */
/* ========================================================================== */

#if T_ISALPHA
void	test_isalpha(void)
{
	int	c;
	int	bad;

	printf("\nft_isalpha\n");
	bad = 0;
	CHAR_LOOP(c)
		if (!ft_isalpha(c) != !isalpha(c))
			bad++;
	CHECK("same as isalpha for EOF..255", bad == 0);
}
#endif

#if T_ISDIGIT
void	test_isdigit(void)
{
	int	c;
	int	bad;

	printf("\nft_isdigit\n");
	bad = 0;
	CHAR_LOOP(c)
		if (!ft_isdigit(c) != !isdigit(c))
			bad++;
	CHECK("same as isdigit for EOF..255", bad == 0);
}
#endif

#if T_ISALNUM
void	test_isalnum(void)
{
	int	c;
	int	bad;

	printf("\nft_isalnum\n");
	bad = 0;
	CHAR_LOOP(c)
		if (!ft_isalnum(c) != !isalnum(c))
			bad++;
	CHECK("same as isalnum for EOF..255", bad == 0);
}
#endif

#if T_ISASCII
void	test_isascii(void)
{
	int	c;
	int	bad;

	printf("\nft_isascii\n");
	bad = 0;
	CHAR_LOOP(c)
		if (!ft_isascii(c) != !isascii(c))
			bad++;
	CHECK("same as isascii for EOF..255", bad == 0);
	CHECK("128 is not ascii", !ft_isascii(128));
	CHECK("-1 is not ascii", !ft_isascii(-1));
}
#endif

#if T_ISPRINT
void	test_isprint(void)
{
	int	c;
	int	bad;

	printf("\nft_isprint\n");
	bad = 0;
	CHAR_LOOP(c)
		if (!ft_isprint(c) != !isprint(c))
			bad++;
	CHECK("same as isprint for EOF..255", bad == 0);
	CHECK("space (32) is printable", ft_isprint(' '));
	CHECK("DEL (127) is not", !ft_isprint(127));
}
#endif

#if T_TOUPPER
void	test_toupper(void)
{
	int	c;
	int	bad;

	printf("\nft_toupper\n");
	bad = 0;
	CHAR_LOOP(c)
		if (ft_toupper(c) != toupper(c))
			bad++;
	CHECK("same as toupper for EOF..255", bad == 0);
}
#endif

#if T_TOLOWER
void	test_tolower(void)
{
	int	c;
	int	bad;

	printf("\nft_tolower\n");
	bad = 0;
	CHAR_LOOP(c)
		if (ft_tolower(c) != tolower(c))
			bad++;
	CHECK("same as tolower for EOF..255", bad == 0);
}
#endif

/* ========================================================================== */
/*  Memory and string functions                                               */
/* ========================================================================== */

#if T_STRLEN
void	test_strlen(void)
{
	printf("\nft_strlen\n");
	CHECK_INT("\"hello\"", ft_strlen("hello"), 5);
	CHECK_INT("empty", ft_strlen(""), 0);
	CHECK_INT("stops at first \\0", ft_strlen("ab\0cd"), 2);
	CHECK_INT("byte > 127", ft_strlen("\xff\x80"), 2);
}
#endif

#if T_MEMSET
void	test_memset(void)
{
	char	a[16];
	char	b[16];

	printf("\nft_memset\n");
	memset(a, 'x', 16);
	memset(b, 'x', 16);
	CHECK("returns dest", ft_memset(a, 'A', 5) == a);
	memset(b, 'A', 5);
	CHECK("5 bytes set, rest untouched", memcmp(a, b, 16) == 0);
	ft_memset(a, 300, 3);
	memset(b, 300, 3);
	CHECK("c > 255 is cut to a byte", memcmp(a, b, 16) == 0);
	ft_memset(a, 'Z', 0);
	CHECK("n = 0 writes nothing", memcmp(a, b, 16) == 0);
}
#endif

#if T_BZERO
void	test_bzero(void)
{
	char	a[8];
	char	b[8];

	printf("\nft_bzero\n");
	memset(a, 'x', 8);
	memset(b, 'x', 8);
	ft_bzero(a, 4);
	memset(b, 0, 4);
	CHECK("first 4 bytes zeroed, rest untouched", memcmp(a, b, 8) == 0);
	ft_bzero(a + 4, 0);
	CHECK("n = 0 writes nothing", memcmp(a, b, 8) == 0);
}
#endif

#if T_MEMCPY
void	test_memcpy(void)
{
	char	dst[16];
	char	src[16];

	printf("\nft_memcpy\n");
	memset(dst, 'x', 16);
	memcpy(src, "hello\0world", 12);
	CHECK("returns dest", ft_memcpy(dst, src, 12) == dst);
	CHECK("copies past a \\0", memcmp(dst, "hello\0world", 12) == 0);
	CHECK("byte after n untouched", dst[12] == 'x');
	CHECK("n = 0 copies nothing", ft_memcpy(dst, "ZZZ", 0) == dst
		&& dst[0] == 'h');
}
#endif

#if T_MEMMOVE
void	test_memmove(void)
{
	char	a[16];
	char	b[16];

	printf("\nft_memmove\n");
	strcpy(a, "123456789");
	strcpy(b, "123456789");
	CHECK("returns dest", ft_memmove(a + 2, a, 5) == a + 2);
	memmove(b + 2, b, 5);
	CHECK("overlap, dest after src", memcmp(a, b, 10) == 0);
	strcpy(a, "123456789");
	strcpy(b, "123456789");
	ft_memmove(a, a + 2, 5);
	memmove(b, b + 2, 5);
	CHECK("overlap, dest before src", memcmp(a, b, 10) == 0);
	ft_memmove(a, "xyz", 3);
	CHECK("no overlap", memcmp(a, "xyz", 3) == 0);
	CHECK("n = 0", ft_memmove(a, a + 1, 0) == a);
}
#endif

#if T_STRLCPY
void	test_strlcpy(void)
{
	const char	*src[] = {"hello", "", "a", "hello world", NULL};
	size_t		sizes[] = {0, 1, 3, 5, 6, 20};
	char		a[32];
	char		b[32];
	int			i;
	int			j;
	char		name[96];

	printf("\nft_strlcpy\n");
	i = -1;
	while (src[++i])
	{
		j = -1;
		while (++j < 6)
		{
			memset(a, 'x', 32);
			memset(b, 'x', 32);
			snprintf(name, sizeof(name), "src \"%s\", size %zu",
				src[i], sizes[j]);
			CHECK(name, ft_strlcpy(a, src[i], sizes[j])
				== ref_strlcpy(b, src[i], sizes[j])
				&& memcmp(a, b, 32) == 0);
		}
	}
}
#endif

#if T_STRLCAT
void	test_strlcat(void)
{
	const char	*dst[] = {"", "abc", "abcdef", NULL};
	const char	*src[] = {"", "xyz", "hello world", NULL};
	size_t		sizes[] = {0, 2, 4, 7, 20};
	char		a[32];
	char		b[32];
	int			i;
	int			j;
	int			k;
	int			bad;

	printf("\nft_strlcat   (every dst x src x size combination)\n");
	bad = 0;
	i = -1;
	while (dst[++i])
	{
		j = -1;
		while (src[++j])
		{
			k = -1;
			while (++k < 5)
			{
				memset(a, 'x', 32);
				memset(b, 'x', 32);
				strcpy(a, dst[i]);
				strcpy(b, dst[i]);
				if (ft_strlcat(a, src[j], sizes[k])
					!= ref_strlcat(b, src[j], sizes[k])
					|| memcmp(a, b, 32) != 0)
				{
					printf("         mismatch: dst \"%s\" src \"%s\" size %zu\n",
						dst[i], src[j], sizes[k]);
					bad++;
				}
			}
		}
	}
	CHECK("all 45 combinations match", bad == 0);
}
#endif

#if T_STRCHR
void	test_strchr(void)
{
	const char	*s = "hello";

	printf("\nft_strchr\n");
	CHECK("first match", ft_strchr(s, 'l') == strchr(s, 'l'));
	CHECK("first char", ft_strchr(s, 'h') == s);
	CHECK("not found -> NULL", ft_strchr(s, 'z') == NULL);
	CHECK("'\\0' -> pointer to end", ft_strchr(s, '\0') == s + 5);
	CHECK("c + 256 acts as c", ft_strchr(s, 'e' + 256) == s + 1);
	CHECK("empty string, 'a'", ft_strchr("", 'a') == NULL);
}
#endif

#if T_STRRCHR
void	test_strrchr(void)
{
	const char	*s = "hello";

	printf("\nft_strrchr\n");
	CHECK("last match", ft_strrchr(s, 'l') == s + 3);
	CHECK("not found -> NULL", ft_strrchr(s, 'z') == NULL);
	CHECK("'\\0' -> pointer to end", ft_strrchr(s, '\0') == s + 5);
	CHECK("c + 256 acts as c", ft_strrchr(s, 'l' + 256) == s + 3);
	CHECK("only first char matches", ft_strrchr(s, 'h') == s);
	CHECK("empty string, 'a'", ft_strrchr("", 'a') == NULL);
}
#endif

#if T_STRNCMP
void	test_strncmp(void)
{
	printf("\nft_strncmp   (only the sign of the result matters)\n");
	CHECK("equal", ft_strncmp("abc", "abc", 3) == 0);
	CHECK("a < b", sign(ft_strncmp("abc", "abd", 3)) == -1);
	CHECK("a > b", sign(ft_strncmp("abd", "abc", 3)) == 1);
	CHECK("differ after n", ft_strncmp("abcX", "abcY", 3) == 0);
	CHECK("n = 0", ft_strncmp("a", "b", 0) == 0);
	CHECK("shorter string", sign(ft_strncmp("ab", "abc", 5)) == -1);
	CHECK("stops at \\0 (n large)", ft_strncmp("ab\0x", "ab\0y", 10) == 0);
	CHECK("byte > 127 is bigger", sign(ft_strncmp("\x80", "\x01", 1))
		== sign(strncmp("\x80", "\x01", 1)));
}
#endif

#if T_MEMCHR
void	test_memchr(void)
{
	const char	s[] = "ab\0cd\xff";

	printf("\nft_memchr\n");
	CHECK("found", ft_memchr(s, 'b', 6) == s + 1);
	CHECK("finds past a \\0", ft_memchr(s, 'd', 6) == s + 4);
	CHECK("finds \\0", ft_memchr(s, '\0', 6) == s + 2);
	CHECK("not in first n", ft_memchr(s, 'c', 3) == NULL);
	CHECK("byte 0xff (c = 255)", ft_memchr(s, 255, 6) == s + 5);
	CHECK("byte 0xff (c = -1)", ft_memchr(s, -1, 6) == s + 5);
	CHECK("n = 0", ft_memchr(s, 'a', 0) == NULL);
}
#endif

#if T_MEMCMP
void	test_memcmp(void)
{
	printf("\nft_memcmp   (only the sign of the result matters)\n");
	CHECK("equal", ft_memcmp("abc", "abc", 3) == 0);
	CHECK("a < b", sign(ft_memcmp("abc", "abd", 3)) == -1);
	CHECK("a > b", sign(ft_memcmp("abd", "abc", 3)) == 1);
	CHECK("compares past \\0", sign(ft_memcmp("a\0b", "a\0c", 3)) == -1);
	CHECK("n = 0", ft_memcmp("a", "b", 0) == 0);
	CHECK("byte 0x80 > 0x01 (unsigned compare)",
		sign(ft_memcmp("\x80", "\x01", 1)) == 1);
	CHECK("byte 0xff > 0x00", sign(ft_memcmp("\xff", "", 1)) == 1);
}
#endif

#if T_STRNSTR
void	test_strnstr(void)
{
	const char	*big = "foo bar baz";
	const char	*little[] = {"bar", "baz", "foo", "", "z", "bar baz x",
		"o b", NULL};
	size_t		lens[] = {0, 1, 3, 6, 7, 11, 50};
	int			i;
	int			j;
	int			bad;

	printf("\nft_strnstr   (every needle x len combination)\n");
	bad = 0;
	i = -1;
	while (little[++i])
	{
		j = -1;
		while (++j < 7)
		{
			if (ft_strnstr(big, little[i], lens[j])
				!= ref_strnstr(big, little[i], lens[j]))
			{
				printf("         mismatch: needle \"%s\" len %zu\n",
					little[i], lens[j]);
				bad++;
			}
		}
	}
	CHECK("all 49 combinations match", bad == 0);
}
#endif

#if T_ATOI
void	test_atoi(void)
{
	const char	*in[] = {"42", "-42", "+42", "   42", "\t\n\v\f\r 42",
		"0042", "42abc", "abc", "", "-", "+-42", "-+42", "--42", " - 42",
		"2147483647", "-2147483648", "0", "-0", "  +0012x", NULL};
	int			i;
	char		name[64];

	printf("\nft_atoi\n");
	i = -1;
	while (in[++i])
	{
		snprintf(name, sizeof(name), "\"%s\"", in[i]);
		CHECK_INT(name, ft_atoi(in[i]), atoi(in[i]));
	}
}
#endif

#if T_CALLOC
void	test_calloc(void)
{
	unsigned char	*p;
	size_t			i;
	int				zero;

	printf("\nft_calloc\n");
	p = ft_calloc(10, 4);
	zero = (p != NULL);
	i = 0;
	while (p && i < 40)
		if (p[i++] != 0)
			zero = 0;
	CHECK("10 x 4: all 40 bytes are 0", zero);
	free(p);
	p = ft_calloc(1, 1);
	CHECK("1 x 1 not NULL", p != NULL && p[0] == 0);
	free(p);
	p = ft_calloc(0, 0);
	CHECK("0 x 0 returns a pointer you can free (like libc)", p != NULL);
	free(p);
	p = ft_calloc(5, 0);
	CHECK("5 x 0 returns a pointer you can free (like libc)", p != NULL);
	free(p);
	p = ft_calloc(SIZE_MAX, 2);
	CHECK("SIZE_MAX x 2 overflows -> NULL", p == NULL);
	free(p);
}
#endif

#if T_STRDUP
void	test_strdup(void)
{
	const char	*s = "hello";
	char		*d;

	printf("\nft_strdup\n");
	d = ft_strdup(s);
	CHECK("same content", d && strcmp(d, s) == 0);
	CHECK("new memory, not the same pointer", d != s);
	free(d);
	d = ft_strdup("");
	CHECK("empty string", d && d[0] == '\0');
	free(d);
}
#endif

/* ========================================================================== */

int	main(void)
{
#if T_ISALPHA
	test_isalpha();
#endif
#if T_ISDIGIT
	test_isdigit();
#endif
#if T_ISALNUM
	test_isalnum();
#endif
#if T_ISASCII
	test_isascii();
#endif
#if T_ISPRINT
	test_isprint();
#endif
#if T_TOUPPER
	test_toupper();
#endif
#if T_TOLOWER
	test_tolower();
#endif
#if T_STRLEN
	test_strlen();
#endif
#if T_MEMSET
	test_memset();
#endif
#if T_BZERO
	test_bzero();
#endif
#if T_MEMCPY
	test_memcpy();
#endif
#if T_MEMMOVE
	test_memmove();
#endif
#if T_STRLCPY
	test_strlcpy();
#endif
#if T_STRLCAT
	test_strlcat();
#endif
#if T_STRCHR
	test_strchr();
#endif
#if T_STRRCHR
	test_strrchr();
#endif
#if T_STRNCMP
	test_strncmp();
#endif
#if T_MEMCHR
	test_memchr();
#endif
#if T_MEMCMP
	test_memcmp();
#endif
#if T_STRNSTR
	test_strnstr();
#endif
#if T_ATOI
	test_atoi();
#endif
#if T_CALLOC
	test_calloc();
#endif
#if T_STRDUP
	test_strdup();
#endif
	printf("\n==== PART 1: %d OK, %d FAIL ====\n", g_pass, g_fail);
	return (g_fail != 0);
}
