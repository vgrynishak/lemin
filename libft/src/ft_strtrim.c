/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:31:37 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/26 19:16:41 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ind_start(char const *s)
{
	int i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	return (i);
}

static int	ind_finish(char const *s)
{
	int i;

	i = ft_strlen(s) - 1;
	while (i != 0 && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i--;
	return (i);
}

char		*ft_strtrim(char const *s)
{
	char	*a;
	int		s_d;
	int		f_d;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	s_d = ind_start(s);
	f_d = ind_finish(s);
	if (s_d > f_d)
		a = (char *)malloc(sizeof(char));
	else if ((a = (char *)malloc(sizeof(char) * ((f_d - s_d) + 2))))
	{
		while (s_d <= f_d)
		{
			a[i] = s[s_d];
			s_d++;
			i++;
		}
	}
	else
		return (NULL);
	a[i] = '\0';
	return (a);
}
