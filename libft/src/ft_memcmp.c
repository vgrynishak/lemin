/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:07:41 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/28 19:09:08 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *us1;
	unsigned char *us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 0 && *us1 == *us2)
	{
		us1++;
		us2++;
		n--;
	}
	if (n == 0)
		return ((unsigned char)(*(us1 - 1)) - (unsigned char)(*(us2 - 1)));
	return ((unsigned char)(*us1) - (unsigned char)(*us2));
}
