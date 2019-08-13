/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:14:18 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/26 18:26:14 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	a = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (a == NULL)
		return (NULL);
	while (*s1)
	{
		a[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		a[i] = *s2;
		s2++;
		i++;
	}
	a[i] = '\0';
	return (a);
}
