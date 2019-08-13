/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:26:03 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/29 15:32:43 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiteri(t_list *lst, void (*f)(unsigned int, t_list *elem))
{
	unsigned int	i;
	t_list			*p;

	i = 0;
	p = lst;
	while (p)
	{
		f(i, p);
		i++;
		p = p->next;
	}
}
