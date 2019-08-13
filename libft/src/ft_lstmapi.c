/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 15:34:43 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/29 15:39:15 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmapi(t_list *lst, t_list *(*f)(unsigned int, t_list *elem))
{
	t_list			*new;
	t_list			*a;
	unsigned int	i;

	i = 0;
	if (lst == NULL)
		return (NULL);
	a = f(i, lst);
	new = a;
	while (lst->next)
	{
		i++;
		lst = lst->next;
		a->next = f(i, lst);
		if (a->next == NULL)
		{
			free(a->next);
			return (NULL);
		}
		a = a->next;
	}
	return (new);
}
