/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:17:21 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/25 12:44:09 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *d;
	unsigned char *s;
	unsigned char uc;

	uc = (unsigned char)c;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n > 0)
	{
		*d = *s;
		if (*d == uc)
			return ((void *)(++d));
		d++;
		s++;
		n--;
	}
	return (NULL);
}
