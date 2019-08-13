/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:30:07 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/28 19:06:16 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
	{
		if (s1[i + 1] == '\0' && s2[i + 1] == '\0')
			return (1);
		i++;
	}
	if (n == 0)
		return (1);
	if (i == n && s1[i - 1] == s2[i - 1])
		return (1);
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	return (0);
}
