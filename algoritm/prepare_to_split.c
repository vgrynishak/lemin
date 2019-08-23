/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_to_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 20:54:36 by vgrynish          #+#    #+#             */
/*   Updated: 2019/08/23 20:55:33 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		*lst_del(t_lst **neighbors)
{
	t_lst		*item;
	void		*data;

	item = *neighbors;
	*neighbors = item->next;
	data = item->content;
	free(item);
	return (data);
}

void		link_delete(t_room *src, t_room *dst)
{
	t_lst		**neighbors;

	neighbors = &src->neighbors;
	while (((t_link *)(*neighbors)->content)->room != dst)
		neighbors = &(*neighbors)->next;
	free(lst_del(neighbors));
}

void		split(t_lemin *lemin, t_link *link)
{
	t_room	*out;
	t_room	*input;

	input = link->room;
	link_delete(lemin->end, input);
	while (input != lemin->start)
	{
		link_delete(input, input->next_save);
		link_delete(input, input->prev_save);
		out = ft_room_new("tmp", 4);
		out->neighbors = input->neighbors;
		input->neighbors = NULL;
		save_conection(input->next_save, out, -1);
		save_conection(out, input, 0);
		if (input->prev_save == lemin->start)
		{
			link_delete(lemin->start, input);
			save_conection(input, lemin->start, -1);
		}
		input = input->prev_save;
	}
}

void		prepare_to_split(t_lemin *lemin)
{
	t_lst		*neighbors;
	t_link		*l;

	neighbors = lemin->end->neighbors;
	while (neighbors)
	{
		l = neighbors->content;
		neighbors = neighbors->next;
		if (l->room->next_save == lemin->end)
			split(lemin, l);
	}
}
