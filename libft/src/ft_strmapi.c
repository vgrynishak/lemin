/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:48:29 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/26 14:49:32 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*c;
	char			*a;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	c = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (c == NULL)
		return (NULL);
	a = c;
	while (s[i])
	{
		*a = f(i, s[i]);
		i++;
		a++;
	}
	*a = '\0';
	return (c);
}
