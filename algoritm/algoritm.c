/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algoritm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 19:43:31 by vgrynish          #+#    #+#             */
/*   Updated: 2019/08/23 20:27:34 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			initial_rooms(t_room *rooms)
{
	t_room	*room_tmp;

	room_tmp = rooms;
	while (room_tmp)
	{
		room_tmp->distance = 1000000;
		room_tmp->prev = NULL;
		room_tmp = room_tmp->next;
	}
}

static void		save_inp(t_room *x)
{
	t_room		*p;
	t_link		*l;
	t_room		*r;

	while ((p = x->prev))
	{
		l = p->neighbors->content;
		if (l->weight == 0)
		{
			r = l->room;
			if (r != x)
				x->prev = r;
			r->prev = p->prev;
		}
		x = x->prev;
	}
}

void			combine_paths(t_lemin *lemin)
{
	t_room		*a;
	t_room		*b;

	b = lemin->end;
	while ((a = b->prev))
	{
		if (a->prev_save != b && b->next_save != a)
		{
			if (a != lemin->start)
				a->next_save = b;
			if (b != lemin->end)
				b->prev_save = a;
		}
		else
		{
			if (a->prev_save == b)
				a->prev_save = NULL;
			if (b->next_save == a)
				b->next_save = NULL;
		}
		b = a;
	}
}

void			restart(t_lemin *lemin)
{
	t_room		*rooms;

	rooms = lemin->rooms;
	while (rooms)
	{
		rooms->distance = 1000000;
		rooms->prev = NULL;
		rooms = rooms->next;
	}
}

int				find_more_path(t_lemin *lemin)
{
	prepare_to_split(lemin);
	find_one_path(lemin);
	save_inp(lemin->end);
	prepare_to_merge(lemin);
	if (!lemin->end->prev)
		return (0);
	combine_paths(lemin);
	restart(lemin);
	return (1);
}
