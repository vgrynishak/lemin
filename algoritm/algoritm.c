#include "lemin.h"

void debug(t_lemin *lemin)
{
    t_room *rooms = lemin->rooms;
    t_lst *neighbors;
    ft_printf("Debug (\n");
    while (rooms)
    {
        ft_printf("  Room \"%s\" %p (\n", rooms->name, rooms);
        ft_printf("    prev:      %s\n", rooms->prev ? rooms->prev->name : "-");
        ft_printf("    prev_save: %s\n", rooms->prev_save ? rooms->prev_save->name : "-");		//
        ft_printf("    next_save: %s\n", rooms->next_save ? rooms->next_save->name : "-");		//
        ft_printf("    neighbors: [");
        neighbors = rooms->neighbors;
        while (neighbors)
        {
            ft_printf(" %s", ((t_link *)neighbors->content)->room->name);
            neighbors = neighbors->next;
        }
        ft_printf(" ]\n  )\n");
        rooms = rooms->next;
    }
    ft_printf(")\n");
}
void initial_rooms(t_room *rooms)
{
    t_room  *room_tmp;
    room_tmp = rooms;

    while (room_tmp)
    {
        room_tmp->distance = 1000000;
        room_tmp->prev = NULL;
        room_tmp = room_tmp->next;
    }
    
}

int is_exist(t_lst *queue, t_room *room)
{
    t_lst *tmp_queue;

    tmp_queue = queue;

    while (tmp_queue)
    {
        if (tmp_queue->content == room) {
            return 1;
        }

        tmp_queue = tmp_queue->next;
    }
    return 0;
}

void			lst_push(t_lst **head, void *data)
{
	t_lst		*item;

	item = (t_lst *)malloc(sizeof(t_lst));
	item->content = data;
	item->next = *head;
	*head = item;
}

void add_to_queue(t_lst **queue, t_room *room)
{
    t_lst *tmp_neighbors;
    t_lst *tmp_queue;   
    t_link *link;

    int new_distance;
    tmp_neighbors = room->neighbors;

    //ft_printf("room: %s\n",room->name );
    while (tmp_neighbors)
    {
        link = tmp_neighbors->content;
        //ft_printf("%s\n",link->room->name );
        new_distance = room->distance + link->weight;  // TODO: add link weight instead of 1
         if (!is_exist(*queue, link->room) && new_distance < link->room->distance) {
            link->room->distance = new_distance;
            link->room->prev = room;
            lst_push(queue, link->room);
           /*  tmp_queue = ft_lst_new(link->room, sizeof(t_room));
            tmp_queue->next = *queue;
            *queue = tmp_queue;*/
        }

        tmp_neighbors = tmp_neighbors->next;
    }
}


t_room *get_min(t_lst **queue)
{
    t_lst *tmp_queue;
    t_lst *prev;
    t_room *min;
    t_lst *tmp_prev;
    t_lst *next;

    min = NULL;
    
    if (!(*queue)) {
        return NULL;
    }

    tmp_queue = *queue;
    while (tmp_queue)
    {
        if (!min) {
            prev = NULL;
            min = tmp_queue->content;
            next = tmp_queue->next;
        }
        else if (min->distance > ((t_room * )tmp_queue->content)->distance) {
            prev = tmp_prev;
            next = tmp_queue->next;
            min = tmp_queue->content;
        }

        tmp_prev = tmp_queue;
        tmp_queue = tmp_queue->next;    
    }
    
    if (!prev) {
        *queue = next;
    } else {
        prev->next = next;
    }
    
    return min;
}

void save_path(t_lemin *lemin)
{
    t_room *t = lemin->end;
    t_room *tmp_next;
    t_room *tmp_prev;

    int check = 1;
    while (t->prev) {
        if (check) {
            tmp_next = t;
            check = 0;  
        } else{
            t->prev_save = t->prev;
            t->next_save = tmp_next;
            tmp_next = t;
        }
        							
        t = t->prev;
    }				
}

void find_one_path(t_lemin *lemin) 
{
    t_lst *queue;
    t_room *src;

    src = lemin->start;
    queue = NULL;
    initial_rooms(lemin->rooms);
    lemin->start->distance = 0;


    while (src && src != lemin->end)
    {   
        add_to_queue(&queue, src);
        src = get_min(&queue);
    }
}

void			*lst_del(t_lst **neighbors)
{
	t_lst		*item;
	void		*data;

	item = *neighbors;
	*neighbors = item->next;
	data = item->content;
	free(item);
	return (data);
}

void			link_delete(t_room *src, t_room *dst)
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
    t_room  *input;
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

void			prepare_to_split(t_lemin *lemin)
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

t_room			*link_pop(t_room *room)
{
	t_room		*dst;

	dst = ((t_link *)room->neighbors->content)->room;
	free(lst_pop(&room->neighbors));
	return (dst);
}

void			*lst_pop(t_lst **room)
{
	t_lst		*item;
	void		*data;

	item = *room;
	*room = item->next;
	data = item->content;
	free(item);
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
		free(output);
		save_conection(input, input->next_save, 1);
		save_conection(input->next_save, input, 1);
		output = prev_output;
	}
	save_conection(lemin->start, input, 1);
	save_conection(input, lemin->start, 1);
}

/*
static void		restore_path(t_room *start, t_room *out, t_room *end)
{
	t_room		*in;
	t_room		*pred_out;

	link_delete(end, out);
	while (out != start)
	{
		in = link_pop(out);
		pred_out = link_pop(in);
		in->links = out->links;
		free(out);
		link_push(in, in->succ, LINK_POSITIVE);
		link_push(in->succ, in, LINK_POSITIVE);
		out = pred_out;
	}
	link_push(start, in, LINK_POSITIVE);
	link_push(in, start, LINK_POSITIVE);
}
 */

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

void		restart(t_lemin *lemin)
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

int			find_more_path(t_lemin *lemin)
{

	prepare_to_split(lemin);

	find_one_path(lemin);

    save_inp(lemin->end);

	prepare_to_merge(lemin);

    if (!lemin->end->prev) {
        return 0;
    }	
	combine_paths(lemin);

   /*  ft_printf("The path: ");			    
    t_room *t = lemin->end;				//
    while (t) {							//
        ft_printf("%s ", t->name);		//
        ft_printf("%p ", t);
        ft_printf("(%s ", t->prev_save ? t->prev_save->name : "-");		//
        ft_printf("%s) ", t->next_save ? t->next_save->name : "-");		//
        t = t->prev;					//
        ft_printf("\n");

    }*/									//
	restart(lemin);

    return 1;
}
