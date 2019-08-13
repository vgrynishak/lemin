/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robota_with_di.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:41:30 by vgrynish          #+#    #+#             */
/*   Updated: 2018/11/22 18:41:31 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*replace_ineger(long long n)
{
	unsigned long long	i;
	char				*c;

	c = BUF_NEW;
	*c = '\0';
	i = (n >= 0) ? n : -n;
	while (i)
	{
		*(--c) = i % 10 + '0';
		i = i / 10;
	}
	return (c);
}

char	*replace_u(unsigned long long n)
{
	char	*c;

	c = BUF_NEW;
	*c = '\0';
	while (n)
	{
		*(--c) = n % 10 + '0';
		n = n / 10;
	}
	return (c);
}

int		robota_with_di(long long n, t_print *p)
{
	char	*c;
	int		n_sign;
	int		n_zero;
	int		n_digits;
	int		len;

	c = replace_ineger(n);
	n_sign = (n < 0 || (*p).flags_plus == 1 || (*p).flags_sp == 1);
	n_digits = ft_strlen(c);
	n_zero = count_zero(n_digits, n_sign, *p);
	len = n_zero + n_digits + n_sign;
	if ((*p).flags_minus == 0 && ((*p).flags_zero == 0 || (*p).precision != -1))
		print_char(' ', (*p).width - len);
	if (n < 0)
		write(1, "-", 1);
	else if ((*p).flags_plus == 1)
		write(1, "+", 1);
	else if ((*p).flags_sp == 1)
		write(1, " ", 1);
	print_char('0', n_zero);
	write(1, c, n_digits);
	if ((*p).flags_minus == 1)
		print_char(' ', (*p).width - len);
	return (((*p).width > len) ? (*p).width : len);
}

int		robota_with_u(unsigned long long n, t_print *p)
{
	char	*c;
	int		n_zero;
	int		n_digits;
	int		len;

	c = replace_u(n);
	n_digits = ft_strlen(c);
	n_zero = count_zero(n_digits, 0, *p);
	len = n_zero + n_digits;
	if ((*p).flags_minus == 0 && ((*p).flags_zero == 0 || (*p).precision != -1))
		print_char(' ', (*p).width - len);
	print_char('0', n_zero);
	write(1, c, n_digits);
	if ((*p).flags_minus == 1)
		print_char(' ', (*p).width - len);
	return (((*p).width > len) ? (*p).width : len);
}
