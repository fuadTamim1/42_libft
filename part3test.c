/* ************************************************************************** */
/*  libft PART 3 tester (bonus: linked lists)  -  do NOT push to your repo    */
/*                                                                            */
/*  Build from your libft folder (after make / make bonus):                   */
/*    cc -Wall -Wextra -Werror -g -fsanitize=address part3test.c libft.a \   */
/*       -I. -o p3 && ./p3                                                    */
/*                                                                            */
/*  MALLOC FAILURE TESTS (T_MALLOC_FAIL): makes malloc fail inside           */
/*  ft_lstnew / ft_lstmap and checks nothing leaks. Needs an extra flag      */
/*  (Linux / WSL only):                                                       */
/*    cc -Wall -Wextra -Werror -g -fsanitize=address part3test.c libft.a \   */
/*       -I. -Wl,--wrap=malloc -o p3 && ./p3                                  */
/*  Keep T_MALLOC_FAIL at 0 if you build without that flag.                  */
/*                                                                            */
/*  How leaks are counted: every content is made by new_content() and freed  */
/*  by del_count(). g_alive = contents made - contents freed. When a list is */
/*  fully freed, g_alive must be back to 0.                                  */
/* ************************************************************************** */

#define T_LSTNEW		1
#define T_LSTADD_FRONT	1
#define T_LSTSIZE		1
#define T_LSTLAST		1
#define T_LSTADD_BACK	1
#define T_LSTDELONE		1
#define T_LSTCLEAR		1
#define T_LSTITER		1
#define T_LSTMAP		1
#define T_MALLOC_FAIL	0

#include "libft.h"
#include <stdio.h>
#include <string.h>

/* ========================================================================== */
/*  Helpers                                                                   */
/* ========================================================================== */

int	g_pass = 0;
int	g_fail = 0;
int	g_alive = 0;
int	g_del_calls = 0;

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

/* a heap copy of s, counted in g_alive */
void	*new_content(const char *s)
{
	g_alive++;
	return (strdup(s));
}

void	del_count(void *content)
{
	g_del_calls++;
	g_alive--;
	free(content);
}

/* list contents as "[a][b][c]" (frees nothing) */
char	*LIST_STR(t_list *lst)
{
	char	*buf;

	buf = calloc(1024, 1);
	while (lst)
	{
		strcat(buf, "[");
		strcat(buf, lst->content ? (char *)lst->content : "(null)");
		strcat(buf, "]");
		lst = lst->next;
	}
	return (buf);
}

/* builds a list WITHOUT your ft_lst* functions, so a bug in one function
   can't make the tests of another one fail */
t_list	*make_list(const char **words)
{
	t_list	*head;
	t_list	**slot;

	head = NULL;
	slot = &head;
	while (*words)
	{
		*slot = calloc(1, sizeof(t_list));
		(*slot)->content = new_content(*words);
		slot = &(*slot)->next;
		words++;
	}
	return (head);
}

/* frees a list WITHOUT your ft_lst* functions */
void	free_list(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		del_count(lst->content);
		free(lst);
		lst = next;
	}
}

/* ========================================================================== */
/*  Tests                                                                     */
/* ========================================================================== */

#if T_LSTNEW
void	test_lstnew(void)
{
	t_list	*n;
	int		x;

	printf("\nft_lstnew\n");
	x = 42;
	n = ft_lstnew(&x);
	CHECK_TRUE("content is the same pointer (not a copy)",
		n && n->content == &x);
	CHECK_TRUE("next is NULL", n && n->next == NULL);
	free(n);
	n = ft_lstnew(NULL);
	CHECK_TRUE("NULL content is allowed", n && n->content == NULL);
	free(n);
}
#endif

#if T_LSTADD_FRONT
void	test_lstadd_front(void)
{
	const char	*w[] = {"b", "c", NULL};
	t_list		*lst;
	t_list		*n;

	printf("\nft_lstadd_front\n");
	lst = make_list(w);
	n = calloc(1, sizeof(t_list));
	n->content = new_content("a");
	ft_lstadd_front(&lst, n);
	CHECK_TRUE("new node is the head", lst == n);
	CHECK("order", LIST_STR(lst), "[a][b][c]");
	free_list(lst);
	lst = NULL;
	n = calloc(1, sizeof(t_list));
	n->content = new_content("x");
	ft_lstadd_front(&lst, n);
	CHECK_TRUE("empty list: node becomes the head",
		lst == n && n->next == NULL);
	free_list(lst);
}
#endif

#if T_LSTSIZE
void	test_lstsize(void)
{
	const char	*w3[] = {"a", "b", "c", NULL};
	const char	*w1[] = {"a", NULL};
	t_list		*lst;

	printf("\nft_lstsize\n");
	CHECK_TRUE("NULL -> 0", ft_lstsize(NULL) == 0);
	lst = make_list(w1);
	CHECK_TRUE("1 node -> 1", ft_lstsize(lst) == 1);
	free_list(lst);
	lst = make_list(w3);
	CHECK_TRUE("3 nodes -> 3", ft_lstsize(lst) == 3);
	free_list(lst);
}
#endif

#if T_LSTLAST
void	test_lstlast(void)
{
	const char	*w3[] = {"a", "b", "c", NULL};
	t_list		*lst;

	printf("\nft_lstlast\n");
	CHECK_TRUE("NULL -> NULL", ft_lstlast(NULL) == NULL);
	lst = make_list(w3);
	CHECK_TRUE("returns the 3rd node", ft_lstlast(lst) == lst->next->next);
	CHECK_TRUE("single node -> itself", ft_lstlast(lst->next->next)
		== lst->next->next);
	free_list(lst);
}
#endif

#if T_LSTADD_BACK
void	test_lstadd_back(void)
{
	const char	*w[] = {"a", "b", NULL};
	t_list		*lst;
	t_list		*n;

	printf("\nft_lstadd_back\n");
	lst = make_list(w);
	n = calloc(1, sizeof(t_list));
	n->content = new_content("c");
	ft_lstadd_back(&lst, n);
	CHECK("added at the end", LIST_STR(lst), "[a][b][c]");
	CHECK_TRUE("head unchanged", strcmp(lst->content, "a") == 0);
	free_list(lst);
	lst = NULL;
	n = calloc(1, sizeof(t_list));
	n->content = new_content("x");
	ft_lstadd_back(&lst, n);
	CHECK_TRUE("empty list: node becomes the head", lst == n);
	free_list(lst);
}
#endif

#if T_LSTDELONE
void	test_lstdelone(void)
{
	const char	*w[] = {"a", "b", NULL};
	t_list		*lst;
	t_list		*second;

	printf("\nft_lstdelone\n");
	lst = make_list(w);
	second = lst->next;
	g_del_calls = 0;
	ft_lstdelone(lst, del_count);
	CHECK_TRUE("del called exactly once", g_del_calls == 1);
	CHECK_TRUE("next node NOT freed", strcmp(second->content, "b") == 0);
	free_list(second);
	CHECK_TRUE("no content leaked", g_alive == 0);
}
#endif

#if T_LSTCLEAR
void	test_lstclear(void)
{
	const char	*w[] = {"a", "b", "c", NULL};
	t_list		*lst;

	printf("\nft_lstclear\n");
	lst = make_list(w);
	g_del_calls = 0;
	ft_lstclear(&lst, del_count);
	CHECK_TRUE("del called for all 3 nodes", g_del_calls == 3);
	CHECK_TRUE("list pointer set to NULL", lst == NULL);
	CHECK_TRUE("no content leaked", g_alive == 0);
	lst = NULL;
	ft_lstclear(&lst, del_count);
	CHECK_TRUE("empty list: no crash", lst == NULL);
}
#endif

#if T_LSTITER
void	upper_first(void *content)
{
	char	*s;

	s = content;
	if (s[0] >= 'a' && s[0] <= 'z')
		s[0] -= 32;
}

void	test_lstiter(void)
{
	const char	*w[] = {"ab", "cd", "ef", NULL};
	t_list		*lst;

	printf("\nft_lstiter\n");
	lst = make_list(w);
	ft_lstiter(lst, upper_first);
	CHECK("f applied to every node", LIST_STR(lst), "[Ab][Cd][Ef]");
	free_list(lst);
	ft_lstiter(NULL, upper_first);
	CHECK_TRUE("NULL list: no crash", 1);
}
#endif

#if T_LSTMAP || T_MALLOC_FAIL
/* returns an uppercased heap copy, counted in g_alive */
void	*dup_upper(void *content)
{
	char	*s;
	int		i;

	s = new_content(content);
	i = 0;
	while (s && s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
		i++;
	}
	return (s);
}
#endif

#if T_LSTMAP
void	test_lstmap(void)
{
	const char	*w3[] = {"ab", "cd", "ef", NULL};
	const char	*w1[] = {"x", NULL};
	t_list		*orig;
	t_list		*res;

	printf("\nft_lstmap\n");
	orig = make_list(w3);
	res = ft_lstmap(orig, dup_upper, del_count);
	CHECK("3 nodes mapped", LIST_STR(res), "[AB][CD][EF]");
	CHECK("original unchanged", LIST_STR(orig), "[ab][cd][ef]");
	CHECK_TRUE("new nodes, not reused", res != NULL && res != orig
		&& res->content != orig->content);
	free_list(res);
	free_list(orig);
	CHECK_TRUE("no content leaked", g_alive == 0);
	orig = make_list(w1);
	res = ft_lstmap(orig, dup_upper, del_count);
	CHECK("single node", LIST_STR(res), "[X]");
	CHECK_TRUE("single: next is NULL", res != NULL && res->next == NULL);
	free_list(res);
	free_list(orig);
	CHECK_TRUE("empty list -> NULL",
		ft_lstmap(NULL, dup_upper, del_count) == NULL);
}
#endif

/* ========================================================================== */
/*  Malloc failure tests                                                      */
/* ========================================================================== */

#if T_MALLOC_FAIL
void	*__real_malloc(size_t size);
int		g_calls_m = 0;
int		g_fail_at = 0;

void	*__wrap_malloc(size_t size)
{
	g_calls_m++;
	if (g_fail_at > 0 && g_calls_m == g_fail_at)
		return (NULL);
	return (__real_malloc(size));
}

void	test_malloc_fail(void)
{
	const char	*w4[] = {"aa", "bb", "cc", "dd", NULL};
	t_list		*orig;
	t_list		*res;
	int			n;
	char		name[96];

	printf("\nmalloc failure\n");
	g_calls_m = 0;
	g_fail_at = 1;
	res = ft_lstnew("x");
	g_fail_at = 0;
	CHECK_TRUE("ft_lstnew: NULL when malloc fails", res == NULL);
	free(res);
	orig = make_list(w4);
	n = 1;
	while (n <= 4)
	{
		g_alive = 4;
		g_calls_m = 0;
		g_fail_at = n;
		res = ft_lstmap(orig, dup_upper, del_count);
		g_fail_at = 0;
		snprintf(name, sizeof(name),
			"ft_lstmap, node #%d fails: NULL and nothing leaked", n);
		CHECK_TRUE(name, res == NULL && g_alive == 4);
		if (res)
			free_list(res);
		n++;
	}
	CHECK("original unchanged", LIST_STR(orig), "[aa][bb][cc][dd]");
	free_list(orig);
}
#endif

/* ========================================================================== */

int	main(void)
{
#if T_LSTNEW
	test_lstnew();
#endif
#if T_LSTADD_FRONT
	test_lstadd_front();
#endif
#if T_LSTSIZE
	test_lstsize();
#endif
#if T_LSTLAST
	test_lstlast();
#endif
#if T_LSTADD_BACK
	test_lstadd_back();
#endif
#if T_LSTDELONE
	test_lstdelone();
#endif
#if T_LSTCLEAR
	test_lstclear();
#endif
#if T_LSTITER
	test_lstiter();
#endif
#if T_LSTMAP
	test_lstmap();
#endif
#if T_MALLOC_FAIL
	test_malloc_fail();
#endif
	printf("\n==== PART 3 (BONUS): %d OK, %d FAIL ====\n", g_pass, g_fail);
	return (g_fail != 0);
}
