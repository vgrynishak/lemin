/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 16:00:10 by vgrynish          #+#    #+#             */
/*   Updated: 2018/11/16 16:00:11 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	main_robota(t_print *p, va_list ap)
{
	int i;

	i = 0;
	if ((*p).type == 'd' || (*p).type == 'i')
		i = robota_with_di(go_size_id(p, ap), &(*p));
	if ((*p).type == 'c' || (*p).type == 's' ||
		(*p).type == '%' || (*p).type == 'p' || p->type == 'f')
		i = robota_with_csvp(p, ap);
	if ((*p).type == 'o' || (*p).type == 'x' ||
		(*p).type == 'X' || (*p).type == 'u' || p->type == 'b')
		i = robota_with_uox(go_size_uox(p, ap), p);
	return (i);
}

int	ft_check_c(const char **c, va_list ap)
{
	int		i;
	t_print	p;

	i = 0;
	(*c)++;
	all_zero(&p);
	ft_define(c, &p, ap);
	if (p.type != '\0')
		i = main_robota(&p, ap);
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	va_start(ap, format);
	while (*format)
	{
		while (*format != '%' && *format != '\0')
		{
			write(1, format, 1);
			format++;
			len++;
		}
		if (*format == '%')
			len = len + ft_check_c(&format, ap);
	}
	va_end(ap);
	return (len);
}
