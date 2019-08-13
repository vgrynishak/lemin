/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:26:35 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/24 14:59:04 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char *y;

	y = NULL;
	while (*s)
	{
		if (*s == (char)c)
			y = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (y);
}
