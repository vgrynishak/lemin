#include "lemin.h"

void fill_room(char **mas, t_room *room)
{
	while (room)
	{
		*mas = room->name;
		mas++;
		room = room->next_save;
	}
	*mas = NULL;	
}

int length_path(t_room *room)
{
	int n;

	n = 0;
	while (room)
	{
		n++;
		room = room->next_save;
	}
	
	return n;
}

void fill_mass(t_lemin *lemin, char ***mas, int *len_mas)
{
	t_lst	*neighbors;
	t_room	*room;
	int		n;
	int		i;

	i = 0;
	neighbors = lemin->start->neighbors;
	while (neighbors) {
		room = ((t_link *)neighbors->content)->room;
		if (room->prev_save == lemin->start) {
			n = length_path(room);
			mas[i] = (char **)malloc(sizeof(char *) * (n + 1));
			len_mas[i] = n;
			fill_room(mas[i], room);
			i++;
		}
		neighbors = neighbors->next;
	}
	len_mas[i] = 0;
	mas[i] = NULL;
}

int count_paths(t_lemin *lemin) {
	int		count;
	t_lst	*neighbors;

	count = 0;
	neighbors = lemin->end->neighbors;
	while (neighbors) {
		if (((t_link *)neighbors->content)->room->next_save == lemin->end)
			++count;	
		neighbors = neighbors->next;
	}
	return count;
}

void find_best_solution(t_lemin *lemin) 
{
   	int g;
	t_solution *solution;

	solution = (t_solution *)malloc(sizeof(t_solution));
	solution->result_paths = NULL;
	solution->result_paths_len = 0;
	g = 0;
	while (find_more_path(lemin))
	{
		g = count_paths(lemin);		
		solution->paths = (char ***)malloc(sizeof(char **) * (g + 1));;
		solution->len_pats = (int *) malloc(sizeof(int) *  (g + 1));
		solution->ants_by_path =  (int *) malloc(sizeof(int) *  (g + 1));
		fill_mass(lemin, solution->paths, solution->len_pats);
		find_line(solution, lemin->count_ant);
		 if (!solution->result_paths || solution->result_line > solution->count_line) {
			solution->result_ants_by_path = solution->ants_by_path;
			solution->result_line = solution->count_line;
			solution->result_paths = solution->paths;
			solution->result_paths_len = solution->len_pats;
		} 
	}
	lemin->solution = solution;
}
