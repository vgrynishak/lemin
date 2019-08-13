/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   robota_with_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 13:16:01 by vgrynish          #+#    #+#             */
/*   Updated: 2018/11/23 13:16:02 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	robota_with_c(char c, t_print *p)
{
	if ((*p).flags_minus == 0 && (*p).flags_zero == 0)
		print_char(' ', (*p).width - 1);
	if ((*p).flags_minus == 0 && (*p).flags_zero == 1)
		print_char('0', (*p).width - 1);
	write(1, &c, 1);
	if ((*p).flags_minus == 1)
		print_char(' ', (*p).width - 1);
	return (((*p).width > 1) ? (*p).width : 1);
}

int	robota_with_s(char *c, t_print *p)
{
	int n_char;
	int len;

	n_char = (c == NULL) ? 6 : ft_strlen(c);
	if ((*p).precision != -1)
		len = (n_char > (*p).precision) ? (*p).precision : n_char;
	else
		len = n_char;
	if ((*p).flags_minus == 0 && (*p).flags_zero == 0)
		print_char(' ', (*p).width - len);
	if ((*p).flags_minus == 0 && (*p).flags_zero == 1)
		print_char('0', (*p).width - len);
	if (c == NULL)
		write(1, "(null)", len);
	else
		write(1, c, len);
	if ((*p).flags_minus == 1)
		print_char(' ', (*p).width - len);
	return (((*p).width > len) ? (*p).width : len);
}

int	robota_with_v(t_print *p)
{
	if ((*p).flags_minus == 0 && (*p).flags_zero == 0)
		print_char(' ', (*p).width - 1);
	if ((*p).flags_minus == 0 && (*p).flags_zero == 1)
		print_char('0', (*p).width - 1);
	write(1, "%", 1);
	if ((*p).flags_minus == 1)
		print_char(' ', (*p).width - 1);
	return ((1 > (*p).width) ? 1 : (*p).width);
}

int	robota_with_p(unsigned long long n, t_print *p)
{
	char	*c;
	int		n_zero;
	int		n_digits;
	int		len;

	c = replace_x(n, 'x');
	n_digits = ft_strlen(c);
	n_zero = count_zero(n_digits, 2, *p);
	len = n_zero + n_digits + 2;
	if ((*p).flags_minus == 0 && ((*p).flags_zero == 0 || (*p).precision != -1))
		print_char(' ', (*p).width - len);
	write(1, "0x", 2);
	print_char('0', n_zero);
	write(1, c, n_digits);
	if ((*p).flags_minus == 1)
		print_char(' ', (*p).width - len);
	return (((*p).width > len) ? (*p).width : len);
}
