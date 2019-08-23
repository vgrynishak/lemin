/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 20:32:19 by vgrynish          #+#    #+#             */
/*   Updated: 2019/08/23 20:38:08 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	find_line(t_solution *solution, int ants)
{
	sort(solution->paths, solution->len_pats);
	main_solution(ants, solution);
}

void	fill_mass(t_lemin *lemin, char ***mas, int *len_mas)
{
	t_lst	*neighbors;
	t_room	*room;
	int		n;
	int		i;

	i = 0;
	neighbors = lemin->start->neighbors;
	while (neighbors)
	{
		room = ((t_link *)neighbors->content)->room;
		if (room->prev_save == lemin->start)
		{
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

void	fill_default_solution(t_solution **solution, int g)
{
	(*solution)->paths = (char ***)malloc(sizeof(char **) * (g + 1));
	(*solution)->len_pats = (int *)malloc(sizeof(int) * (g + 1));
	(*solution)->ants_by_path = (int *)malloc(sizeof(int) * (g + 1));
}

void	find_best_solution(t_lemin *lemin)
{
	int			g;
	t_solution	*solution;

	solution = (t_solution *)malloc(sizeof(t_solution));
	solution->result_paths = NULL;
	solution->result_paths_len = 0;
	g = 0;
	while (find_more_path(lemin))
	{
		g = count_paths(lemin);
		fill_default_solution(&solution, g);
		fill_mass(lemin, solution->paths, solution->len_pats);
		find_line(solution, lemin->count_ant);
		if (!solution->result_paths || solution->result_line
		> solution->count_line)
		{
			free_solution(solution->result_paths, solution->result_paths_len,
			solution->result_ants_by_path);
			fill_solution(solution);
		}
		else
			free_solution(solution->paths, solution->len_pats,
			solution->ants_by_path);
	}
	lemin->solution = solution;
}
