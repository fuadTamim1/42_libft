/* ************************************************************************** */
/*  libft PART 2 tester (additional functions)  -  do NOT push to your repo   */
/*                                                                            */
/*  Build from your libft folder (after make):                                */
/*    cc -Wall -Wextra -Werror -g -fsanitize=address part2test.c libft.a \   */
/*       -I. -o p2 && ./p2                                                    */
/*                                                                            */
/*  MALLOC FAILURE TESTS (T_MALLOC_FAIL): makes malloc fail on purpose and   */
/*  checks the function returns NULL and frees everything it allocated.      */
/*  Needs two extra linker flags (Linux / WSL only):                         */
/*    cc -Wall -Wextra -Werror -g -fsanitize=address part2test.c libft.a \   */
/*       -I. -Wl,--wrap=malloc -Wl,--wrap=free -o p2 && ./p2                 */
/*  Keep T_MALLOC_FAIL at 0 if you build without those flags.                */
/*                                                                            */
/*  Set a switch to 0 to skip a function (it then doesn't need to exist).    */
/* ************************************************************************** */

#define T_SUBSTR		1
#define T_STRJOIN		1
#define T_STRTRIM		1
#define T_SPLIT			1
#define T_ITOA			1
#define T_STRMAPI		1
#define T_STRITERI		1
#define T_PUTCHAR		1
#define T_PUTSTR		1
#define T_PUTENDL		1
#define T_PUTNBR		1
#define T_MALLOC_FAIL	0

#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>

/* ========================================================================== */
/*  Helpers                                                                   */
/* ========================================================================== */

int	g_pass = 0;
int	g_fail = 0;

/* compares two strings, frees got */
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

/* turns a split result into "[a][b][c]" and frees the array */
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

/* FD_START() gives an fd to write to; FD_RESULT(fd) returns what was written */
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
/*  Tests                                                                     */
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
	char	s1[] = "ab";
	char	s2[] = "cd";

	printf("\nft_strjoin\n");
	CHECK("normal", ft_strjoin("ab", "cd"), "abcd");
	CHECK("empty s1", ft_strjoin("", "cd"), "cd");
	CHECK("empty s2", ft_strjoin("ab", ""), "ab");
	CHECK("both empty", ft_strjoin("", ""), "");
	CHECK("longer", ft_strjoin("hello ", "world"), "hello world");
	free(ft_strjoin(s1, s2));
	CHECK_TRUE("inputs unchanged", strcmp(s1, "ab") == 0
		&& strcmp(s2, "cd") == 0);
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
	CHECK("single kept", ft_strtrim("a", "x"), "a");
	CHECK("empty set", ft_strtrim("abc", ""), "abc");
	CHECK("empty s1", ft_strtrim("", "abc"), "");
	CHECK("both empty", ft_strtrim("", ""), "");
	CHECK("nothing to trim", ft_strtrim("abc", "xyz"), "abc");
	CHECK("only front", ft_strtrim("xxabc", "x"), "abc");
	CHECK("only back", ft_strtrim("abcxx", "x"), "abc");
}
#endif

#if T_SPLIT
void	test_split(void)
{
	printf("\nft_split   (result shown as [word][word]...)\n");
	CHECK("extra spaces", JOINED(ft_split("  hello  world ", ' ')),
		"[hello][world]");
	CHECK("empty string", JOINED(ft_split("", ' ')), "");
	CHECK("only delimiters", JOINED(ft_split(",,,,", ',')), "");
	CHECK("no delimiter", JOINED(ft_split("hello", ' ')), "[hello]");
	CHECK("c == '\\0'", JOINED(ft_split("hello", '\0')), "[hello]");
	CHECK("empty fields", JOINED(ft_split("a,b,,c,", ',')), "[a][b][c]");
	CHECK("leading delim", JOINED(ft_split(",a", ',')), "[a]");
	CHECK("trailing delim", JOINED(ft_split("a,", ',')), "[a]");
	CHECK("single char words", JOINED(ft_split("a b c", ' ')), "[a][b][c]");
	CHECK("three words", JOINED(ft_split("one two three", ' ')),
		"[one][two][three]");
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

#if T_STRMAPI || T_MALLOC_FAIL
char	upper_even(unsigned int i, char c)
{
	if (i % 2 == 0 && c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
#endif

#if T_STRMAPI
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
/*  Malloc failure tests                                                      */
/*  Every malloc/free in your libft goes through the two wrappers below.      */
/*  g_live = blocks your code still holds. After a failed call it must be 0.  */
/* ========================================================================== */

#if T_MALLOC_FAIL
void	*__real_malloc(size_t size);
void	__real_free(void *p);
int		g_calls_m = 0;
int		g_fail_at = 0;
int		g_live = 0;

void	*__wrap_malloc(size_t size)
{
	void	*p;

	g_calls_m++;
	if (g_fail_at > 0 && g_calls_m == g_fail_at)
		return (NULL);
	p = __real_malloc(size);
	if (p)
		g_live++;
	return (p);
}

void	__wrap_free(void *p)
{
	if (p)
		g_live--;
	__real_free(p);
}

void	arm(int n)
{
	g_calls_m = 0;
	g_live = 0;
	g_fail_at = n;
}

/* first malloc fails: function must return NULL and hold nothing */
void	fail_first(const char *name, void *result)
{
	char	buf[96];

	g_fail_at = 0;
	snprintf(buf, sizeof(buf), "%s: NULL when malloc fails", name);
	CHECK_TRUE(buf, result == NULL);
	if (result)
		free(result);
}

void	test_malloc_fail(void)
{
	char	**res;
	int		n;
	char	name[96];

	printf("\nmalloc failure\n");
	arm(1);
	fail_first("ft_substr", ft_substr("hello", 1, 3));
	arm(1);
	fail_first("ft_strjoin", ft_strjoin("ab", "cd"));
	arm(1);
	fail_first("ft_strtrim", ft_strtrim("  ab  ", " "));
	arm(1);
	fail_first("ft_itoa", ft_itoa(-42));
	arm(1);
	fail_first("ft_strmapi", ft_strmapi("abc", upper_even));
	n = 1;
	while (n <= 4)
	{
		arm(n);
		res = ft_split("one two three", ' ');
		g_fail_at = 0;
		snprintf(name, sizeof(name),
			"ft_split, malloc #%d fails: NULL and nothing leaked", n);
		CHECK_TRUE(name, res == NULL && g_live == 0);
		if (res)
			free(JOINED(res));
		n++;
	}
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
#if T_MALLOC_FAIL
	test_malloc_fail();
#endif
	printf("\n==== PART 2: %d OK, %d FAIL ====\n", g_pass, g_fail);
	return (g_fail != 0);
}
