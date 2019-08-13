/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicod.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 18:40:49 by vgrynish          #+#    #+#             */
/*   Updated: 2018/12/02 18:40:50 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		robota_with_unicode(char *c, wchar_t unicod)
{
	int i;

	i = 0;
	if (unicod < 128)
		c[i++] = (char)unicod;
	else if (unicod < 2048)
	{
		c[i++] = (unicod >> 6) | 192;
		c[i++] = (unicod & 63) | 128;
	}
	else if (unicod < 65536)
	{
		c[i++] = (unicod >> 12) | 224;
		c[i++] = ((unicod >> 6) & 63) | 128;
		c[i++] = (unicod & 63) | 128;
	}
	else
	{
		c[i++] = (unicod >> 18) | 270;
		c[i++] = ((unicod >> 12) & 63) | 128;
		c[i++] = ((unicod >> 6) & 63) | 128;
		c[i++] = (unicod & 63) | 128;
	}
	c[i] = '\0';
}

int			robota_with_c_unicode(wchar_t c, t_print *p)
{
	char	*a;
	int		len;

	a = g_buffer;
	robota_with_unicode(a, c);
	len = ft_strlen(a);
	if ((*p).flags_minus == 0 && (*p).flags_zero == 0)
		print_char(' ', (*p).width - len);
	if ((*p).flags_minus == 0 && (*p).flags_zero == 1)
		print_char('0', (*p).width - len);
	write(1, a, len);
	if ((*p).flags_minus == 1)
		print_char(' ', (*p).width - len);
	return (((*p).width > len) ? (*p).width : len);
}

long double	work_with_n(long double n)
{
	union u_double		x;
	int					pown;

	n = (n >= 0) ? n : -n;
	x.d = n;
	pown = (x.i << 1 >> 53) - 1023;
	if (pown < 0)
		return (0.);
	if (pown < 52)
		x.i = x.i >> (52 - pown) << (52 - pown);
	return (x.d);
}

long double	work_with_ln(long double n)
{
	union u_long_double		x;
	int						pown;

	n = (n >= 0) ? n : -n;
	x.d = n;
	pown = ((((x.i).exp) << 1) >> 1) - 16383;
	if (pown < 0)
		return (0.);
	if (pown < 63)
		((x.i).mts) = ((x.i).mts) >> (63 - pown) << (63 - pown);
	return (x.d);
}
