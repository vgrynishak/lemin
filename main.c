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

void	initial_lemin(t_lemin **lemin) 
{
	*lemin = (t_lemin *)malloc(sizeof(t_lemin));
	
	(*lemin)->input = NULL;
	(*lemin)->count_ant = 0;
	(*lemin)->start = NULL;
	(*lemin)->end = NULL;
	(*lemin)->rooms = NULL;
	(*lemin)->error = 0;
	
}

void show(t_link *link)
{
	t_room *room;
	room = link->room;

	ft_printf("The path: ");			//
	while (room) {							//
		ft_printf("%s ", room->name);		//
		ft_printf("(%s ", room->prev_save ? room->prev_save->name : "-");		//
		ft_printf("%s) ", room->next_save ? room->next_save->name : "-");		//
		room = room->prev_save;					//
	}									//
	ft_printf("\n");
}

int start_to_finish(t_lemin *lemin)
{
	t_room *rooms;
	t_lst *neighbors;
	rooms = lemin->rooms;

	while (rooms)
	{
		if (rooms == lemin->start) {
			neighbors = rooms->neighbors;
			while (neighbors)
			{
				if (((t_link *)neighbors->content)->room == lemin->end) {
					return 1;
				}
				neighbors = neighbors->next;
			}
			break ;
		}
		rooms = rooms->next;
	}
	return 0;
}

void show_input_line(t_lemin *lemin)
{
	int i;

	i = 1;
	while (i <= lemin->count_ant)
	{
		if (i == lemin->count_ant)
			ft_printf("L%d-%s\n", i, lemin->end->name);
		else
			ft_printf("L%d-%s ", i, lemin->end->name);
		i++;	
	}
	exit (1);
}

int main(void)
{
	t_lemin	*lemin;
	char	*line;

	initial_lemin(&lemin);
	while (get_next_line(0, &line) == 1)
	{
		save_input(lemin, line);
		parse_data(lemin, line);
		free(line);
		if (lemin->error) {
			write(1, "ERROR\n", 6);
			return 1;
		}		
	}
	
	if (!lemin->input) {
		write(1, "ERROR\n", 6);
		return 1;
	}
	if (start_to_finish(lemin))
		show_input_line(lemin);
	find_best_solution(lemin);
	//minus_by_patchs(lemin->solution);

	//system("leaks -q lem-in >&2");exit(1);

	if (!lemin->solution->result_paths)
		write(1, "ERROR\n", 6);
	else {
		show_input(lemin, lemin->solution);
	system("leaks -q lem-in >&2");exit(1);
	}

	return (1);
}	
void show_patch(t_lemin *lemin) {	
	t_solution *solution = lemin->solution;
	/* int *tre = solution->result_ants_by_path;
	while (*tre)
	{
		ft_printf("%d\n", *tre);
		tre++;
	}
	exit(1);*/
	t_input *input;
	t_input *input_go;
	char ***mas;
	int *len_mas;
	int ant_go = 1;
	input = NULL;
	int i = 0; 
	while (i < solution->result_line)
	{
		if (!input) {
			input = (t_input *)malloc(sizeof(t_input));
			input = NULL;
			input_start_go(solution, &ant_go, &input);
		} else {
			go_one_step(&input, lemin, solution);
			input_start_go(solution, &ant_go, &input);
		}
		input_go = input;

		while (input_go)
		{
			ft_printf("L%d-%s ", input_go->ant_number, input_go->room_name);
			input_go = input_go->next;
		}
		ft_printf("\n");
		/* int *tre = solution->result_ants_by_path;
		while (*tre)
		{
			ft_printf("%d\n", *tre);
			tre++;
		}*/
//		exit(1);
		i++;
	}
	
	//ft_printf("%d\n", solution->result_line);
	//exit(1);
	mas = solution->result_paths;
	len_mas = solution->result_ants_by_path;

	while (*mas)
	{
		 char **tmp;
		tmp = *mas;
		while (*tmp)
		{
			ft_printf("%s ", *tmp);
			tmp++;
		}
		ft_printf("\n");
		ft_printf("len %d\n", *len_mas);
		mas++;
		len_mas++;
	}
	
	exit(1);
	find_more_path(lemin);
	

							
/* 	t_lst *neighbors;
	t_link *l;

	neighbors = lemin->end->neighbors;
	while (neighbors)
	{
		l = neighbors->content;
		ft_printf("%s\n", l->room->prev_save->name);
		neighbors = neighbors->next;
		if (l->room->next_save == lemin->end)
			show(l);
	}exit(1);*/
	// print the path from end to start:	//	TEST
	{										//
		ft_printf("The path: ");			//
		t_room *t = lemin->end;				//
		while (t) {							//
			ft_printf("%s ", t->name);		//
			ft_printf("(%s ", t->prev_save ? t->prev_save->name : "-");		//
			ft_printf("%s) ", t->next_save ? t->next_save->name : "-");		//
			t = t->prev;					//
		}									//
		ft_printf("\n");					//
	}										//

/* 
	t_lst *ngb = lemin->start->neighbors;

	 while (ngb)
	{
		ft_printf("%s\n",((t_link *)ngb->content)->room->name );
		t_lst *tmp = ((t_link *)ngb->content)->room->neighbors;
		ft_putstr("neighbors: ");
		while (tmp)
		{
			ft_printf("%s\n",((t_link *)tmp->content)->room->name );
			tmp = tmp->next;
		}
		write (1, "\n", 1);
		ngb = ngb->next;
	}exit(1);
	 
	write(1, "input\n", 6);

	t_lst  *tmp1;

	tmp1 = lemin->input;
	while (tmp1) {
		ft_printf("%s\n", tmp1->content);
		tmp1 = tmp1->next;
	}

	write(1, "room\n", 5);
	t_room  *tmp2;

	tmp2 = lemin->rooms;

	while (tmp2) {
		ft_printf("%s\n", tmp2->name);
		tmp2= tmp2->next;
	}

	write(1, "connect\n", 8);
	t_room  *tmp3;

	tmp3 = lemin->rooms;

	while (tmp3) {
		t_lst *links;
		
		ft_printf("%s: ", tmp3->name);
		
		links = tmp3->neighbors;
		while (links)
		{
			ft_printf("%s [", ((t_link *)(links->content))->room->name);
			t_lst *tmp =((t_link *)(links->content))->room->neighbors;
			while (tmp)
			{
				ft_printf("%s ", ((t_link *)(tmp->content))->room->name);
				tmp = tmp->next;
			}
			ft_printf("] ");
			links = links->next;
		}
		
		ft_printf("\n");
		tmp3= tmp3->next;
	}*/
}
