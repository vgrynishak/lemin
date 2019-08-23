/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_solution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 20:20:29 by vgrynish          #+#    #+#             */
/*   Updated: 2019/08/23 20:21:27 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	fill_room(char **mas, t_room *room)
{
	while (room)
	{
		*mas = room->name;
		mas++;
		room = room->next_save;
	}
	*mas = NULL;
}

int		length_path(t_room *room)
{
	int n;

	n = 0;
	while (room)
	{
		n++;
		room = room->next_save;
	}
	return (n);
}

int		count_paths(t_lemin *lemin)
{
	int		count;
	t_lst	*neighbors;

	count = 0;
	neighbors = lemin->end->neighbors;
	while (neighbors)
	{
		if (((t_link *)neighbors->content)->room->next_save == lemin->end)
			++count;
		neighbors = neighbors->next;
	}
	return (count);
}

void	free_solution(char ***paths, int *len_mas, int *ants_by_path)
{
	char	***mas;

	if (paths)
	{
		mas = paths;
		while (*mas)
		{
			free(*mas);
			mas++;
		}
		free(paths);
		free(len_mas);
		free(ants_by_path);
	}
}

void	fill_solution(t_solution *solution)
{
	solution->result_ants_by_path = solution->ants_by_path;
	solution->result_line = solution->count_line;
	solution->result_paths = solution->paths;
	solution->result_paths_len = solution->len_pats;
}
