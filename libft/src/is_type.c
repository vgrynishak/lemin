/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:20:32 by vgrynish          #+#    #+#             */
/*   Updated: 2018/11/22 18:20:33 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_type(char c)
{
	int			i;
	const char	type[] = "cspdiouxXf%b";

	i = 0;
	while (type[i])
	{
		if (c == type[i])
			return (1);
		i++;
	}
	return (0);
}

void	all_zero(t_print *p)
{
	(*p).width = 0;
	(*p).precision = -1;
	(*p).flags_grill = 0;
	(*p).flags_sp = 0;
	(*p).flags_plus = 0;
	(*p).flags_minus = 0;
	(*p).flags_zero = 0;
	(*p).size = 0;
}

int		count_zero(int n_digits, int n_sign, t_print p)
{
	if (p.precision != -1)
	{
		if (p.precision - n_digits > 0)
			return (p.precision - n_digits);
	}
	else if (p.flags_minus == 0 && p.flags_zero == 1)
	{
		if (p.width - n_digits - n_sign > 0)
			return (p.width - n_digits - n_sign);
		else if (n_digits == 0)
			return (1);
	}
	else if (n_digits == 0)
		return (1);
	return (0);
}

void	print_char(char c, int n)
{
	while (n > 0)
	{
		write(1, &c, 1);
		n--;
	}
}
