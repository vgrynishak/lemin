/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robota_with_f.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:34:37 by vgrynish          #+#    #+#             */
/*   Updated: 2018/11/24 20:34:38 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*write_d(long double n)
{
	int			y;
	char		*c;
	long double	x;
	int			s;

	s = 0;
	x = 1.;
	c = g_buffer;
	if (n == 0.)
		c[s++] = '0';
	else
	{
		while (x <= n / 10)
			x *= 10.;
		while (x >= 1)
		{
			y = (int)((n / x));
			c[s++] = y + '0';
			n = n - y * x;
			x /= 10.;
		}
	}
	c[s] = '\0';
	return (c);
}

long double		check(long double n, t_print p)
{
	int			pr;
	long double	i;

	i = 1.;
	pr = (p.precision == -1) ? 6 : p.precision;
	while (pr)
	{
		i *= .1;
		n = n * 10 - work_with_ln(n * 10);
		pr--;
	}
	if (n >= .5)
		return (i * .5);
	return (0.);
}

char			*write_after_coma(long double n, t_print p)
{
	int		z;
	char	*c;
	int		i;
	int		y;

	i = 0;
	c = BUF_NEW - BUFFPF_SIZE;
	z = (p.precision == -1) ? 6 : p.precision;
	while (z--)
	{
		y = (int)(n * 10);
		c[i++] = y + '0';
		n = n * 10 - y;
	}
	c[i] = '\0';
	return (c);
}

void			define_str(t_float *f, long double n, t_print p)
{
	f->n_sign = (n < 0 || p.flags_plus == 1 || p.flags_sp == 1);
	n = (n >= 0) ? n : -n;
	f->n_int = (p.size == 5) ? work_with_ln(n) : work_with_n(n);
	n = n + check(n - f->n_int, p);
	f->n_int = (p.size == 5) ? work_with_ln(n) : work_with_n(n);
	f->c = write_d(f->n_int);
	f->a = write_after_coma(n - f->n_int, p);
	f->n_coma = (p.precision != 0 || p.flags_grill == 1) ? 1 : 0;
	f->n_digit = ft_strlen(f->c);
	f->n_digit2 = ft_strlen(f->a);
	f->len = f->n_sign + f->n_digit + f->n_coma + f->n_digit2;
	if (p.flags_minus == 0 && p.flags_zero == 1)
	{
		if (p.width - f->len > 0)
			f->n_zero = p.width - f->len;
	}
	else
		f->n_zero = 0;
	f->len = f->n_sign + f->n_digit + f->n_coma + f->n_digit2 + f->n_zero;
}

int				robota_with_f(long double n, t_print *p)
{
	t_float f;

	define_str(&f, n, *p);
	if ((*p).flags_minus == 0 && ((*p).flags_zero == 0))
		print_char(' ', (*p).width - f.len);
	if (n < 0)
		write(1, "-", 1);
	else if (p->flags_plus == 1)
		write(1, "+", 1);
	else if (p->flags_sp == 1)
		write(1, " ", 1);
	print_char('0', f.n_zero);
	write(1, f.c, f.n_digit);
	write(1, ".", f.n_coma);
	write(1, f.a, f.n_digit2);
	if ((*p).flags_minus == 1)
		print_char(' ', (*p).width - f.len);
	return (((*p).width > f.len) ? (*p).width : f.len);
}
