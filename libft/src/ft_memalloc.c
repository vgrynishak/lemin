/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:01:37 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/26 17:14:33 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	unsigned char	*a;
	unsigned int	i;

	i = 0;
	a = (unsigned char*)malloc(sizeof(unsigned char) * size);
	if (a == NULL)
		return (NULL);
	while (i < size)
	{
		a[i] = '\0';
		i++;
	}
	return ((void *)a);
}
