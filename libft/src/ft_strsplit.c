/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:47:44 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/26 21:07:26 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	numworld(char const *s, char c)
{
	int i;
	int n;

	n = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			n++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (n);
}

static int	len_world(char const *s, char c)
{
	int y;

	y = 0;
	while (*s && *s != c)
	{
		s++;
		y++;
	}
	return (y);
}

static void	copy(char *c, const char *s, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		c[i] = s[i];
		i++;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	char	**a;
	int		num;
	int		len;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	num = numworld(s, c);
	a = (char **)malloc(sizeof(char *) * (num + 1));
	if (a == NULL)
		return (NULL);
	while (i < num)
	{
		while (*s == c)
			s++;
		len = len_world(s, c);
		a[i] = (char *)malloc(sizeof(char) * (len + 1));
		copy(a[i], s, len);
		a[i][len] = '\0';
		s = s + len;
		i++;
	}
	a[num] = NULL;
	return (a);
}
