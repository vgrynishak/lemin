/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:16:29 by vgrynish          #+#    #+#             */
/*   Updated: 2018/11/22 18:16:30 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	is_flags(const char **c, t_print *p)
{
	while (**c == ' ' || **c == '-' || **c == '+' || **c == '#' || **c == '0')
	{
		if (**c == ' ')
			(*p).flags_sp = 1;
		if (**c == '-')
			(*p).flags_minus = 1;
		if (**c == '+')
			(*p).flags_plus = 1;
		if (**c == '#')
			(*p).flags_grill = 1;
		if (**c == '0')
			(*p).flags_zero = 1;
		(*c)++;
	}
}

static void	is_width(const char **c, t_print *p, va_list ap)
{
	int n;

	n = 0;
	if (**c == '*')
	{
		(*c)++;
		n = va_arg(ap, int);
		if (n < 0)
		{
			n = -n;
			p->flags_minus = 1;
		}
	}
	else
	{
		while (**c >= '0' && **c <= '9')
		{
			n = n * 10 + (**c) - '0';
			(*c)++;
		}
	}
	(*p).width = n;
}

static void	is_precisin(const char **c, t_print *p, va_list ap)
{
	int n;

	n = 0;
	while (**c == '.')
		(*c)++;
	if (**c == '*')
	{
		(*c)++;
		n = va_arg(ap, int);
		if (n < 0)
		{
			(*p).precision = -1;
			return ;
		}
	}
	else
	{
		while (**c >= '0' && **c <= '9')
		{
			n = n * 10 + (**c) - '0';
			(*c)++;
		}
	}
	(*p).precision = n;
}

static void	is_size(const char **c, t_print *p)
{
	while (**c == 'L' || **c == 'l' || **c == 'h' || **c == 'j'
		|| **c == 'z')
		(*c)++;
	if (*(*c - 1) == 'L')
		(*p).size = 5;
	if (*(*c - 1) == 'j')
		(*p).size = 6;
	if (*(*c - 1) == 'z')
		(*p).size = 7;
	if (*((*c) - 1) == 'h')
	{
		if (*((*c) - 2) == 'h')
			(*p).size = 3;
		else
			(*p).size = 1;
	}
	if (*((*c) - 1) == 'l')
	{
		if (*((*c) - 2) == 'l')
			(*p).size = 4;
		else
			(*p).size = 2;
	}
}

void		ft_define(const char **c, t_print *p, va_list ap)
{
	while (is_type(**c) == 0 && **c)
	{
		if (**c == ' ' || **c == '-' || **c == '+' || **c == '#' || **c == '0')
			is_flags(c, p);
		else if ((**c >= '1' && **c <= '9') || **c == '*')
			is_width(c, p, ap);
		else if (**c == '.')
			is_precisin(c, p, ap);
		else if (**c == 'h' || **c == 'l' || **c == 'L' || **c == 'j' ||
			**c == 'z')
			is_size(c, p);
		else
			(*c)++;
	}
	(*p).type = **c;
	if (**c != '\0')
		(*c)++;
}
