/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 19:57:50 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/24 20:20:27 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *ub;
	unsigned char uc;

	ub = (unsigned char *)b;
	uc = (unsigned char)c;
	while (len > 0)
	{
		*ub = uc;
		ub++;
		len--;
	}
	return (b);
}
