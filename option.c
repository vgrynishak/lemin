#include "lemin.h"

void show_patch(t_solution *solution) {	
	
	char ***mas;
	mas = solution->result_paths;
	ft_printf("Result paths: \n");
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
		mas++;
	}
}

void check_argv(int argc, char **argv, t_lemin *lemin)
{
	if (argc > 1) {
		if (!ft_strcmp(argv[1], "-p"))
			lemin->show_option = 1;
		else if (!ft_strcmp(argv[1], "-l"))
			lemin->show_option = 2;
		else if (!ft_strcmp(argv[1], "-r"))
			lemin->show_option = 3;	
		else
			lemin->show_option = 0;
	}
}

void debug(t_lemin *lemin)
{
    t_room *rooms;
    t_lst *neighbors;

	rooms = lemin->rooms;
    ft_printf("Debug (\n");
    while (rooms)
    {
        ft_printf("  Room \"%s\" %p (\n", rooms->name, rooms);
        ft_printf("    prev:      %s\n", rooms->prev ? rooms->prev->name : "-");
        ft_printf("    prev_save: %s\n", rooms->prev_save ? rooms->prev_save->name : "-");
        ft_printf("    next_save: %s\n", rooms->next_save ? rooms->next_save->name : "-");
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
	(*lemin)->show_option = 0;
	(*lemin)->error = 0;
	
}