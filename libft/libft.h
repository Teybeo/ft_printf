/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 12:49:52 by tdarchiv          #+#    #+#             */
/*   Updated: 2018/10/29 19:25:55 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define ALLOW_SILENT_FAIL (1)

# include <stddef.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			*ft_memset(void *dest, int value, size_t count);
void			ft_bzero(void *src, size_t count);
void			*ft_memcpy(void *dst, const void *src, size_t count);
void			*ft_memccpy(void *dest, const void *src, int stop, size_t size);
void			*ft_memmove(void *dst, const void *src, size_t count);
void			*ft_memchr(const void *s, int c, size_t count);
int				ft_memcmp(const void *s1, const void *s2, size_t count);

size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_strcpy(char *dest, char const *src);
char			*ft_strncpy(char *dest, char const *src, size_t n);
char			*ft_strcat(char *dest, char const *src);
char			*ft_strncat(char *dest, char const *src, size_t nb);
size_t			ft_strlcat(char *dest, char const *src, size_t size);
char			*ft_strstr(char const *str, char const *to_find);
char			*ft_strnstr(char const *s, char const *to_find, size_t length);
int				ft_strcmp(char const *s1, char const *s2);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
char			*ft_strchr(char const *s, int c);
char			*ft_strrchr(char const *s, int c);
char			*ft_str_to_lower(char *str);
char			*ft_str_to_upper(char *str);

int				ft_atoi(char const *str);
int				ft_atoi_base(char const *str, char const *base, int base_len);
char			*ft_itoa(int n);
char			*ft_itoa_sign(int n, char plus_sign);
char			*ft_ltoa(long nb);
char			*ft_ltoa_sign(long nb, char plus_sign);
char			*ft_lutoa_sign(unsigned long nb, char plus_sign);
char			*ft_itoa_base(int nb, char const *base, int base_len);

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_isascii(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

int				ft_max(int a, int b);

void			*ft_memalloc(size_t size);
void			ft_memdel(void **data);
char			*ft_realloc(char *buffer, size_t current_size, size_t new_size);

void			ft_strdel(char **data);
char			*ft_strnew(size_t size);

void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *string, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *string, char (*fn)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int				ft_strequ(char const *a, char const *b);
int				ft_strnequ(char const *a, char const *b, size_t count);

char			*ft_strsub(char const *string, size_t start, size_t length);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *input, char c);
char			**ft_strsplit_charset(char *input, char *charset);

void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr(int nb);
void			ft_putnbr_fd(int nb, int fd);

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **list, void (*del_fn)(void*, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void(*fn)(t_list *elem));
t_list			*ft_lstmap(t_list *ptr, t_list *(*fn)(t_list *elem));
void			ft_list_push_back(t_list **begin_list, void *data, size_t size);

#endif
