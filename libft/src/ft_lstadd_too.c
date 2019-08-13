/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_too.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 20:09:31 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/28 20:32:40 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	ft_lstadd_too(t_list **alst, t_list *new)
{
	t_list *p;

	if (*alst == NULL)
		*alst = new;
	else
	{
		p = *alst;
		while (p->next)
			p = p->next;
		p->next = new;
	}
}
