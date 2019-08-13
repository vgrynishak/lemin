/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 22:53:46 by vgrynish          #+#    #+#             */
/*   Updated: 2018/11/24 22:53:47 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					robota_with_uox(unsigned long long n, t_print *p)
{
	int i;

	if ((*p).type == 'o')
		i = robota_with_o(n, &(*p));
	if ((*p).type == 'x' || p->type == 'X')
		i = robota_with_x(n, &(*p));
	if ((*p).type == 'u')
		i = robota_with_u(n, &(*p));
	if ((*p).type == 'b')
		i = robota_with_b(n, &(*p));
	return (i);
}

long long			go_size_id(t_print *p, va_list ap)
{
	long long n;

	if ((*p).size == 1)
		n = (short)va_arg(ap, int);
	else if (p->size == 6)
		n = va_arg(ap, intmax_t);
	else if (p->size == 7)
		n = va_arg(ap, ssize_t);
	else if ((*p).size == 2)
		n = va_arg(ap, long);
	else if ((*p).size == 3)
		n = (char)va_arg(ap, int);
	else if ((*p).size == 4)
		n = va_arg(ap, long long);
	else
		n = va_arg(ap, int);
	return (n);
}

unsigned long long	go_size_uox(t_print *p, va_list ap)
{
	unsigned long long t;

	if ((*p).size == 1)
		t = (unsigned short)va_arg(ap, int);
	else if (p->size == 6)
		t = va_arg(ap, uintmax_t);
	else if (p->size == 7)
		t = va_arg(ap, size_t);
	else if ((*p).size == 2)
		t = va_arg(ap, unsigned long);
	else if ((*p).size == 3)
		t = (unsigned char)va_arg(ap, int);
	else if ((*p).size == 4)
		t = va_arg(ap, unsigned long long);
	else
		t = va_arg(ap, unsigned int);
	return (t);
}

int					robota_with_csvp(t_print *p, va_list ap)
{
	int i;

	if (p->type == 'c')
	{
		if (p->size == 2)
			i = robota_with_c_unicode(va_arg(ap, wchar_t), p);
		else
			i = robota_with_c(va_arg(ap, int), p);
	}
	if (p->type == 's')
		i = robota_with_s(va_arg(ap, char *), p);
	if (p->type == '%')
		i = robota_with_v(p);
	if (p->type == 'p')
		i = robota_with_p(va_arg(ap, unsigned long long), p);
	if (p->type == 'f')
	{
		if (p->size == 5)
			i = robota_with_f(va_arg(ap, long double), p);
		else
			i = robota_with_f(va_arg(ap, double), p);
	}
	return (i);
}
