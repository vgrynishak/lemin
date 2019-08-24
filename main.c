#include "lemin.h"

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
	show_start(lemin);
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

int	show_finaly_input(t_lemin *lemin)
{
	if (!lemin->input)
	{
		write(1, "ERROR\n", 6);
		return 1;
	}
	if (start_to_finish(lemin))
		show_input_line(lemin);
	find_best_solution(lemin);
	if (!lemin->solution->result_paths)
		write(1, "ERROR\n", 6);
	else{
		show_input(lemin, lemin->solution);
		if (lemin->show_option == 1)
			show_patch(lemin->solution);
		if (lemin->show_option == 2)
			ft_printf("Result line: %d\n", lemin->solution->result_line);
		if (lemin->show_option == 3)
			debug(lemin);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	t_lemin	*lemin;
	char	*line;

	initial_lemin(&lemin);
	check_argv(argc, argv, lemin);
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
	return show_finaly_input(lemin);
}

