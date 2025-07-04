/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:10:56 by himousta          #+#    #+#             */
/*   Updated: 2024/11/15 15:10:20 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>

// garbeg collector
typedef struct g_collector
{
	void				*node;
	struct g_collector	*next;	
}	t_gc;

// struct for envs (list)
typedef struct env
{
	char		*key;
	char		*value;
	int			flag_exported;
	t_gc		*head_gc;
	struct env	*next;
}	t_env;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// garbeg collect
char	*clean_and_null(t_env *envs);
void	clean_memory(t_gc **head);
void	*g_collector(size_t size, t_env *envs);

int		is_allowed(char c);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len); //not complete yet
void	*ft_memset(void *b, int c, size_t len);

void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *hstack, const char *needle, size_t hist_len);
char	*ft_strrchr(const char *s, int chistory_length);
char	*ft_strtrim(char const *s1, char const *set, t_env *envp);
char	*ft_substr(char const *s, unsigned int start, size_t len, t_env *envs);

int		ft_tolower(int chistory_length);
int		ft_toupper(int chistory_length);

// added envs
char	**ft_split(char const *s, char c, t_env *envs);
char	*ft_strdup(const char *s1, t_env *envs);
char	*ft_itoa(int n, t_env *envs);
char	*ft_strjoin(char const *s1, char const *s2, t_env *envs);

#endif
