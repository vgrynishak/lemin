/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 11:09:37 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/27 12:12:58 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char		*replace(char *dst, int i)
{
	char	*f;
	int		j;

	j = 0;
	f = (char *)malloc(sizeof(char) * (i + 1));
	if (f == NULL)
		return (NULL);
	while (j < i)
	{
		f[j] = dst[i - 1 - j];
		j++;
	}
	f[j] = '\0';
	return (f);
}

char			*ft_itoa(int k)
{
	char			a[33];
	int				i;
	unsigned int	n;

	n = (k >= 0) ? k : -k;
	i = 0;
	if (n == 0)
	{
		a[i] = '0';
		i++;
	}
	while (n)
	{
		a[i] = n % 10 + '0';
		i++;
		n = n / 10;
	}
	if (k < 0)
	{
		a[i] = '-';
		i++;
	}
	return (replace(a, i));
}
