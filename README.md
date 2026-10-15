*This project has been created as part of the 42 curriculum by ftamimi.*

# libft

## Description

libft is my own C library. It is the first project of the 42 core curriculum: I rewrote a set of functions from the C standard library, then added extra functions for strings, output and linked lists. Later 42 projects use this library instead of libc.

Everything is written from scratch in C, follows the 42 Norm, and uses only three external functions: `malloc`, `free` and `write`.

### Part 1 — libc functions

Same behavior as the original libc functions, with an `ft_` prefix.

| Group | Functions |
| --- | --- |
| Character checks | `ft_isalpha` `ft_isdigit` `ft_isalnum` `ft_isascii` `ft_isprint` |
| Case conversion | `ft_toupper` `ft_tolower` |
| Strings | `ft_strlen` `ft_strlcpy` `ft_strlcat` `ft_strchr` `ft_strrchr` `ft_strncmp` `ft_strnstr` `ft_strdup` |
| Memory | `ft_memset` `ft_bzero` `ft_memcpy` `ft_memmove` `ft_memchr` `ft_memcmp` `ft_calloc` |
| Conversion | `ft_atoi` |

### Part 2 — additional functions

Functions that are not in libc, or that work differently.

| Function | What it does |
| --- | --- |
| `ft_substr` | Returns a new string: part of `s`, starting at `start`, at most `len` characters |
| `ft_strjoin` | Returns a new string: `s1` followed by `s2` |
| `ft_strtrim` | Returns a copy of `s1` without the characters of `set` at the start and end |
| `ft_split` | Splits a string on a delimiter character into a NULL-terminated array of words |
| `ft_itoa` | Converts an int to a string (handles negatives and `INT_MIN`) |
| `ft_strmapi` | Returns a new string where each character is `f(index, char)` |
| `ft_striteri` | Calls `f(index, &char)` on each character, changing the string in place |
| `ft_putchar_fd` | Writes a character to a file descriptor |
| `ft_putstr_fd` | Writes a string to a file descriptor |
| `ft_putendl_fd` | Writes a string followed by a newline to a file descriptor |
| `ft_putnbr_fd` | Writes an int to a file descriptor, without allocating memory |

### Linked lists

The library includes a simple singly linked list:

```c
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
```

| Function | What it does |
| --- | --- |
| `ft_lstnew` | Creates a new node |
| `ft_lstadd_front` | Adds a node at the beginning of a list |
| `ft_lstadd_back` | Adds a node at the end of a list |
| `ft_lstsize` | Counts the nodes in a list |
| `ft_lstlast` | Returns the last node |
| `ft_lstdelone` | Frees one node and its content |
| `ft_lstclear` | Frees a node and every node after it |
| `ft_lstiter` | Applies a function to the content of every node |
| `ft_lstmap` | Builds a new list by applying a function to every node's content |

## Instructions

### Build

```sh
make        # builds libft.a
make clean  # removes the .o files
make fclean # removes the .o files and libft.a
make re     # rebuilds everything from scratch
```

Everything is compiled with `cc -Wall -Wextra -Werror`.

### Use it in a project

Include the header in your code:

```c
#include "libft.h"

int	main(void)
{
	char	*s;

	s = ft_itoa(-42);
	ft_putendl_fd(s, 1);
	free(s);
	return (0);
}
```

Then compile with the library:

```sh
cc -Wall -Wextra -Werror main.c -L. -lft -o program
```

Every file was also checked with `norminette`.

## Resources

- The Linux man pages for the original functions: https://man7.org/linux/man-pages/

### Use of AI

I used Claude (an AI assistant) as a tutor, not to write the library. I used it to:

- explain what each Part 2 and linked-list function must do, and which edge cases to handle
- review code I had written and point out bugs, such as a missing `+ 1` in an allocation, an unsigned underflow in `ft_strtrim`, and a missed cleanup on failure in `ft_split`
- write the test program I used, which is not part of the library
- fix Norm formatting (42 headers, tabs, alignment, blank lines) and mark helper functions `static`, without changing any logic
- help draft this README

All the code in the library is my own.
