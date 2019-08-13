/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:29:15 by vgrynish          #+#    #+#             */
/*   Updated: 2018/10/27 13:58:16 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *p;

	p = NULL;
	p = (t_list *)malloc(sizeof(t_list));
	if (p == NULL)
		return (NULL);
	if (content == NULL || content_size == 0)
	{
		p->content = NULL;
		p->content_size = 0;
	}
	else if ((p->content = (void *)malloc(sizeof(void) * content_size)))
	{
		ft_memcpy(p->content, content, content_size);
		p->content_size = content_size;
	}
	else
	{
		free(p);
		p = NULL;
	}
	p->next = NULL;
	return (p);
}
