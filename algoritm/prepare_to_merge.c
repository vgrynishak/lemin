#include "lemin.h"

t_room			*link_pop(t_room *room)
{
	t_room		*dst;

	dst = ((t_link *)room->neighbors->content)->room;
	free(lst_del(&room->neighbors));
	return (dst);
}


static void		merge(t_lemin *lemin, t_link *l)
{
	t_room		*input;
	t_room		*prev_output;
    t_room *output;

    output = l->room;
	link_delete(lemin->end, output);
	while (output != lemin->start)
	{
        input = link_pop(output);
		prev_output = link_pop(input);
		input->neighbors = output->neighbors;
		free(output->name);
		free(output);
		save_conection(input, input->next_save, 1);
		save_conection(input->next_save, input, 1);
		output = prev_output;
	}
	save_conection(lemin->start, input, 1);
	save_conection(input, lemin->start, 1);
}

void			prepare_to_merge(t_lemin *lemin)
{
	t_lst		*neighbors;
	t_link		*l;

	neighbors = lemin->end->neighbors;
	while (neighbors)
	{
		l = neighbors->content;
		neighbors = neighbors->next;
		if (l->weight == -1)
			merge(lemin, l);
	}
}