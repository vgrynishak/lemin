/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 18:41:34 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/26 15:02:41 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strnew(size_t size)
{
	char *c;
	char *a;

	c = NULL;
	c = (char *)malloc(sizeof(char) * (size + 1));
	a = c;
	if (c == NULL)
		return (NULL);
	while (size > 0)
	{
		*a++ = '\0';
		size--;
	}
	*a = '\0';
	return (c);
}
