/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:31:40 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/27 15:02:32 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *p;
	t_list *a;

	if (lst == NULL)
		return (NULL);
	a = f(lst);
	p = a;
	while (lst->next)
	{
		lst = lst->next;
		a->next = f(lst);
		if (a->next == NULL)
		{
			free(a->next);
			return (NULL);
		}
		a = a->next;
	}
	return (p);
}
