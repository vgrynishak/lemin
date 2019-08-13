/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:42:39 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/25 13:54:52 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *us;

	us = (unsigned char *)s;
	while (n > 0)
	{
		if (*us == (unsigned char)c)
			return ((void *)us);
		us++;
		n--;
	}
	return (NULL);
}
