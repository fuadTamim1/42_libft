/* ************************************************************************** */
/*  libft Part 2 tester  -  do NOT push this file to your libft repo          */
/*                                                                            */
/*  Build:                                                                    */
/*    cc -Wall -Wextra -Werror -g -fsanitize=address main.c libft.a -o test   */
/*    ./test                                                                  */
/*                                                                            */
/*  HOW TO USE                                                                */
/*  1. Pick what to test: set the switches below to 1 (run) or 0 (skip).      */
/*     A skipped function is not compiled, so it doesn't need to exist yet.   */
/*  2. Add a test case: copy one CHECK line inside that function's block.     */
/*  3. Add a new function: copy any block (#if ... #endif), rename it,        */
/*     add a switch below, and add one line in main().                        */
/* ************************************************************************** */

#define T_SUBSTR	0
#define T_STRJOIN	0
#define T_STRTRIM	0
#define T_SPLIT		1
#define T_ITOA		0
#define T_STRMAPI	0
#define T_STRITERI	0
#define T_PUTCHAR	0
#define T_PUTSTR	0
#define T_PUTENDL	0
#define T_PUTNBR	0

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>

/* ========================================================================== */
/*  Helpers - you shouldn't need to touch these                               */
/* ========================================================================== */

int	g_pass = 0;
int	g_fail = 0;

/* CHECK(name, got, expected): compare two strings, free got */
void	CHECK(const char *name, char *got, const char *exp)
{
	if (got && exp && strcmp(got, exp) == 0)
	{
		g_pass++;
		printf("  [OK]   %s\n", name);
	}
	else
	{
		g_fail++;
		printf("  [FAIL] %s\n         got: \"%s\"\n         exp: \"%s\"\n",
			name, got ? got : "(NULL)", exp ? exp : "(NULL)");
	}
	free(got);
}

/* CHECK_TRUE(name, condition): passes if condition is non-zero */
void	CHECK_TRUE(const char *name, int ok)
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

/* turns a split result into "[a][b][c]", frees the array */
char	*JOINED(char **arr)
{
	char	*buf;
	int		i;

	if (!arr)
		return (NULL);
	buf = calloc(1024, 1);
	i = 0;
	while (arr[i])
	{
		strcat(buf, "[");
		strcat(buf, arr[i]);
		strcat(buf, "]");
		free(arr[i]);
		i++;
	}
	free(arr);
	return (buf);
}

/* FD_START() gives you a fd to write to; FD_RESULT(fd) returns what was written */
int	FD_START(void)
{
	return (open("tester.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644));
}

char	*FD_RESULT(int fd)
{
	char	*buf;
	ssize_t	n;

	buf = calloc(256, 1);
	lseek(fd, 0, SEEK_SET);
	n = read(fd, buf, 255);
	if (n < 0)
		n = 0;
	buf[n] = '\0';
	close(fd);
	unlink("tester.tmp");
	return (buf);
}

/* ========================================================================== */
/*  Tests - one block per function                                            */
/* ========================================================================== */

#if T_SUBSTR
void	test_substr(void)
{
	printf("\nft_substr\n");
	CHECK("middle", ft_substr("hello", 1, 3), "ell");
	CHECK("whole string", ft_substr("hello", 0, 5), "hello");
	CHECK("len past end", ft_substr("hello", 2, 100), "llo");
	CHECK("len SIZE_MAX", ft_substr("hello", 0, SIZE_MAX), "hello");
	CHECK("len 0", ft_substr("hello", 2, 0), "");
	CHECK("start == strlen", ft_substr("hello", 5, 2), "");
	CHECK("start > strlen", ft_substr("hello", 100, 2), "");
	CHECK("start UINT_MAX", ft_substr("hello", UINT_MAX, 2), "");
	CHECK("empty s", ft_substr("", 0, 5), "");
	CHECK("last char", ft_substr("hello", 4, 1), "o");
}
#endif

#if T_STRJOIN
void	test_strjoin(void)
{
	printf("\nft_strjoin\n");
	CHECK("normal", ft_strjoin("ab", "cd"), "abcd");
	CHECK("empty s1", ft_strjoin("", "cd"), "cd");
	CHECK("empty s2", ft_strjoin("ab", ""), "ab");
	CHECK("both empty", ft_strjoin("", ""), "");
	CHECK("longer", ft_strjoin("hello ", "world"), "hello world");
}
#endif

#if T_STRTRIM
void	test_strtrim(void)
{
	printf("\nft_strtrim\n");
	CHECK("subject example", ft_strtrim("xxhexllox", "x"), "hexllo");
	CHECK("spaces", ft_strtrim("   hi  ", " "), "hi");
	CHECK("multi-char set", ft_strtrim("ababcxba", "ab"), "cx");
	CHECK("middle kept", ft_strtrim(" a b ", " "), "a b");
	CHECK("all trimmed", ft_strtrim("xxxx", "x"), "");
	CHECK("single trimmed", ft_strtrim("x", "x"), "");
	CHECK("empty set", ft_strtrim("abc", ""), "abc");
	CHECK("empty s1", ft_strtrim("", "abc"), "");
	CHECK("nothing to trim", ft_strtrim("abc", "xyz"), "abc");
	CHECK("only front", ft_strtrim("xxabc", "x"), "abc");
	CHECK("only back", ft_strtrim("abcxx", "x"), "abc");
}
#endif

#if T_SPLIT
void	test_split(void)
{
	printf("\nft_split   (result shown as [word][word]...)\n");
	CHECK("extra spaces", JOINED(ft_split("  hello  world ", ' ')), "[hello][world]");
	CHECK("empty string", JOINED(ft_split("", ' ')), "");
	CHECK("only delimiters", JOINED(ft_split(",,,,", ',')), "");
	CHECK("no delimiter", JOINED(ft_split("hello", ' ')), "[hello]");
	CHECK("c == '\\0'", JOINED(ft_split("hello", '\0')), "[hello]");
	CHECK("empty fields", JOINED(ft_split("a,b,,c,", ',')), "[a][b][c]");
	CHECK("leading delim", JOINED(ft_split(",a", ',')), "[a]");
	CHECK("trailing delim", JOINED(ft_split("a,", ',')), "[a]");
	CHECK("three words", JOINED(ft_split("one two three", ' ')), "[one][two][three]");
}
#endif

#if T_ITOA
void	test_itoa(void)
{
	printf("\nft_itoa\n");
	CHECK("0", ft_itoa(0), "0");
	CHECK("-1", ft_itoa(-1), "-1");
	CHECK("9", ft_itoa(9), "9");
	CHECK("10", ft_itoa(10), "10");
	CHECK("-10", ft_itoa(-10), "-10");
	CHECK("42", ft_itoa(42), "42");
	CHECK("1000000", ft_itoa(1000000), "1000000");
	CHECK("INT_MAX", ft_itoa(INT_MAX), "2147483647");
	CHECK("INT_MIN", ft_itoa(INT_MIN), "-2147483648");
}
#endif

#if T_STRMAPI
char	upper_even(unsigned int i, char c)
{
	if (i % 2 == 0 && c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

char	add_index(unsigned int i, char c)
{
	return (c + i);
}

void	test_strmapi(void)
{
	char	src[] = "hello";

	printf("\nft_strmapi\n");
	CHECK("upper even index", ft_strmapi("hello", upper_even), "HeLlO");
	CHECK("add index", ft_strmapi("aaaa", add_index), "abcd");
	CHECK("empty string", ft_strmapi("", upper_even), "");
	free(ft_strmapi(src, upper_even));
	CHECK_TRUE("original unchanged", strcmp(src, "hello") == 0);
}
#endif

#if T_STRITERI
int	g_calls = 0;

void	upper_even_ptr(unsigned int i, char *c)
{
	g_calls++;
	if (i % 2 == 0 && *c >= 'a' && *c <= 'z')
		*c -= 32;
}

void	test_striteri(void)
{
	char	s[] = "hello";
	char	empty[] = "";

	printf("\nft_striteri\n");
	ft_striteri(s, upper_even_ptr);
	CHECK("modified in place", strdup(s), "HeLlO");
	CHECK_TRUE("f called 5 times", g_calls == 5);
	g_calls = 0;
	ft_striteri(empty, upper_even_ptr);
	CHECK_TRUE("empty: f never called", g_calls == 0);
}
#endif

#if T_PUTCHAR
void	test_putchar(void)
{
	int	fd;

	printf("\nft_putchar_fd\n");
	fd = FD_START();
	ft_putchar_fd('a', fd);
	CHECK("'a'", FD_RESULT(fd), "a");
	fd = FD_START();
	ft_putchar_fd('\n', fd);
	CHECK("'\\n'", FD_RESULT(fd), "\n");
}
#endif

#if T_PUTSTR
void	test_putstr(void)
{
	int	fd;

	printf("\nft_putstr_fd\n");
	fd = FD_START();
	ft_putstr_fd("hello", fd);
	CHECK("hello", FD_RESULT(fd), "hello");
	fd = FD_START();
	ft_putstr_fd("", fd);
	CHECK("empty string", FD_RESULT(fd), "");
}
#endif

#if T_PUTENDL
void	test_putendl(void)
{
	int	fd;

	printf("\nft_putendl_fd\n");
	fd = FD_START();
	ft_putendl_fd("hi", fd);
	CHECK("hi", FD_RESULT(fd), "hi\n");
	fd = FD_START();
	ft_putendl_fd("", fd);
	CHECK("empty string", FD_RESULT(fd), "\n");
}
#endif

#if T_PUTNBR
void	test_putnbr(void)
{
	int	fd;

	printf("\nft_putnbr_fd\n");
	fd = FD_START();
	ft_putnbr_fd(0, fd);
	CHECK("0", FD_RESULT(fd), "0");
	fd = FD_START();
	ft_putnbr_fd(-42, fd);
	CHECK("-42", FD_RESULT(fd), "-42");
	fd = FD_START();
	ft_putnbr_fd(10, fd);
	CHECK("10", FD_RESULT(fd), "10");
	fd = FD_START();
	ft_putnbr_fd(INT_MAX, fd);
	CHECK("INT_MAX", FD_RESULT(fd), "2147483647");
	fd = FD_START();
	ft_putnbr_fd(INT_MIN, fd);
	CHECK("INT_MIN", FD_RESULT(fd), "-2147483648");
}
#endif

/* ========================================================================== */

int	main(void)
{
#if T_SUBSTR
	test_substr();
#endif
#if T_STRJOIN
	test_strjoin();
#endif
#if T_STRTRIM
	test_strtrim();
#endif
#if T_SPLIT
	test_split();
#endif
#if T_ITOA
	test_itoa();
#endif
#if T_STRMAPI
	test_strmapi();
#endif
#if T_STRITERI
	test_striteri();
#endif
#if T_PUTCHAR
	test_putchar();
#endif
#if T_PUTSTR
	test_putstr();
#endif
#if T_PUTENDL
	test_putendl();
#endif
#if T_PUTNBR
	test_putnbr();
#endif
	printf("\n==== %d OK, %d FAIL ====\n", g_pass, g_fail);
	return (g_fail != 0);
}