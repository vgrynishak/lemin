/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:32:02 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/24 15:46:32 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*det;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	det = (char *)(malloc(sizeof(char) * (i + 1)));
	if (det == 0)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		det[i] = s1[i];
		i++;
	}
	det[i] = '\0';
	return (det);
}
