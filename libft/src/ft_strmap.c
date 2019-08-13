/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:46:50 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/26 14:48:17 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *c;
	char *a;

	if (s == NULL)
		return (NULL);
	c = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (c == NULL)
		return (NULL);
	a = c;
	while (*s)
	{
		*a = f(*s);
		a++;
		s++;
	}
	*a = '\0';
	return (c);
}
