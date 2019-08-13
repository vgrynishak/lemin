/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robota_with_oxX.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:42:55 by vgrynish          #+#    #+#             */
/*   Updated: 2018/11/23 14:42:56 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*replace_ob(unsigned long long n, int base)
{
	char	*c;

	c = BUF_NEW;
	*c = '\0';
	while (n)
	{
		*(--c) = n % base + '0';
		n = n / base;
	}
	return (c);
}

char	*replace_x(unsigned long long n, char type)
{
	unsigned long long	i;
	char				*c;
	char				a;

	a = (type == 'x') ? 'a' : 'A';
	c = BUF_NEW;
	*c = '\0';
	while (n)
	{
		i = n % 16;
		if (i < 10)
			*(--c) = i + '0';
		else if (i > 9 && i <= 15)
			*(--c) = a + i - 10;
		n = n / 16;
	}
	return (c);
}

int		robota_with_o(unsigned long long n, t_print *p)
{
	char	*c;
	int		n_sign;
	int		n_zero;
	int		n_digits;
	int		len;

	c = replace_ob(n, 8);
	n_digits = ft_strlen(c);
	if ((*p).precision <= n_digits)
		n_sign = ((*p).flags_grill == 0) ? 0 : 1;
	else
		n_sign = 0;
	n_zero = (count_zero(n_digits, n_sign, *p) == 1 && n_sign == 1 &&
	n_digits == 0) ? 0 : count_zero(n_digits, n_sign, *p);
	len = n_zero + n_digits + n_sign;
	if ((*p).flags_minus == 0 && ((*p).flags_zero == 0 || (*p).precision != -1))
		print_char(' ', (*p).width - len);
	write(1, "0", n_sign);
	print_char('0', n_zero);
	write(1, c, n_digits);
	if ((*p).flags_minus == 1)
		print_char(' ', (*p).width - len);
	return (((*p).width > len) ? (*p).width : len);
}

int		robota_with_x(unsigned long long n, t_print *p)
{
	char	*c;
	int		n_sign;
	int		n_zero;
	int		n_digits;
	int		len;

	c = replace_x(n, p->type);
	n_digits = ft_strlen(c);
	if (n_digits != 0)
		n_sign = ((*p).flags_grill == 0) ? 0 : 2;
	else
		n_sign = 0;
	n_zero = count_zero(n_digits, n_sign, *p);
	len = n_zero + n_digits + n_sign;
	if ((*p).flags_minus == 0 && ((*p).flags_zero == 0 || (*p).precision != -1))
		print_char(' ', (*p).width - len);
	if (p->type == 'x')
		write(1, "0x", n_sign);
	else
		write(1, "0X", n_sign);
	print_char('0', n_zero);
	write(1, c, n_digits);
	if ((*p).flags_minus == 1)
		print_char(' ', (*p).width - len);
	return (((*p).width > len) ? (*p).width : len);
}

int		robota_with_b(unsigned long long n, t_print *p)
{
	char	*c;
	int		n_sign;
	int		n_zero;
	int		n_digits;
	int		len;

	c = replace_ob(n, 2);
	n_digits = ft_strlen(c);
	if (n_digits != 0)
		n_sign = ((*p).flags_grill == 0) ? 0 : 2;
	else
		n_sign = 0;
	n_zero = count_zero(n_digits, n_sign, *p);
	len = n_zero + n_digits + n_sign;
	if ((*p).flags_minus == 0 && ((*p).flags_zero == 0 || (*p).precision != -1))
		print_char(' ', (*p).width - len);
	write(1, "0b", n_sign);
	print_char('0', n_zero);
	write(1, c, n_digits);
	if ((*p).flags_minus == 1)
		print_char(' ', (*p).width - len);
	return (((*p).width > len) ? (*p).width : len);
}
