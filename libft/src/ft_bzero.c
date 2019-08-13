/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:46:04 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/25 11:25:59 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char *us;

	us = (unsigned char *)s;
	while (n > 0)
	{
		*us = '\0';
		us++;
		n--;
	}
}
