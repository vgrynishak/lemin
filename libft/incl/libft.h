/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 15:56:47 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/29 16:12:15 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <inttypes.h>
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PINK "\e[35m"
# define WHITE "\e[37m"
# define BUFFPF_SIZE 1024

char					g_buffer[BUFFPF_SIZE + 1];
char					g_buf[BUFFPF_SIZE + 1];
# define BUF_NEW  g_buf + BUFFPF_SIZE
# define BUFF_SIZE 32

typedef struct			s_print
{
	int					width;
	int					precision;
	unsigned int		flags_grill;
	unsigned int		flags_zero;
	unsigned int		flags_minus;
	unsigned int		flags_plus;
	unsigned int		flags_sp;
	char				type;
	unsigned int		size;
}						t_print;

typedef struct			s_float
{
	char				*c;
	char				*a;
	int					len;
	int					n_sign;
	int					n_digit;
	long double			n_int;
	int					n_coma;
	int					n_zero;
	int					n_digit2;
}						t_float;

typedef struct			s_like
{
	unsigned long long	mts;
	short int			exp;
}						t_like;

union					u_double
{
	unsigned long long	i;
	double				d;
};

union					u_long_double
{
	t_like				i;
	long double			d;
};

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_gnl
{
	int					fd;
	int					start;
	int					finish;
	char				after_n[BUFF_SIZE];
	struct s_gnl		*next;
}						t_gnl;

int						get_next_line(const int fd, char **line);
int						ft_lstnum(t_list *lst);
t_list					*ft_lstmapi(t_list *lst, t_list *(*f)(unsigned int,
										t_list *elem));
void					ft_lstiteri(t_list *lst, void (*f)(unsigned int,
											t_list *elem));
void					ft_swap(char **a, char **b);
void					ft_lstadd_too(t_list **alst, t_list *new);
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstdelone(t_list **alst, void (*del)
									(void *, size_t));
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_isprint(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isalpha(int c);
int						ft_isalnum(int c);
int						ft_atoi(const char *str);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strnstr(const char *haystack,
								const char *needle, size_t len);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strrchr(const char *s, int c);
char					*ft_strchr(const char *s, int c);
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *s1);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src,
									int c, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, char
								(*f)(unsigned int, char));
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s, unsigned int
								start, size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);
char					*ft_itoa(int n);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_define(const char **c, t_print *p, va_list ap);
int						is_type(char c);
void					all_zero(t_print *p);
int						robota_with_di(long long n, t_print *p);
int						robota_with_c(char c, t_print *p);
void					print_char(char c, int n);
int						robota_with_s(char *c, t_print *p);
int						robota_with_v(t_print *p);
int						robota_with_o(unsigned long long n, t_print *p);
int						robota_with_x(unsigned long long n, t_print *p);
int						ft_printf(const char *format, ...);
int						robota_with_u(unsigned long long n, t_print *p);
int						count_zero(int n_digits, int n_sign, t_print p);
unsigned long long		go_size_uox(t_print *p, va_list ap);
long long				go_size_id(t_print *p, va_list ap);
int						robota_with_uox(unsigned long long n, t_print *p);
int						robota_with_f(long double n, t_print *p);
char					*replace_x(unsigned long long n, char type);
int						robota_with_p(unsigned long long n, t_print *p);
int						robota_with_b(unsigned long long n, t_print *p);
long double				work_with_ln(long double n);
long double				work_with_n(long double n);
int						robota_with_c_unicode(wchar_t c, t_print *p);
int						robota_with_csvp(t_print *p, va_list ap);
int						ft_abs(int i);

#endif
