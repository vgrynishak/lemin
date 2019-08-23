/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 19:56:08 by vgrynish          #+#    #+#             */
/*   Updated: 2019/08/23 20:08:44 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	minus_by_patchs(t_solution *solution)
{
	int	*tre;

	tre = solution->result_ants_by_path;
	while (*tre)
	{
		*tre -= 1;
		tre++;
	}
}

void	add_to_input(t_input **input, t_input *add, int *ant_go)
{
	t_input *lol;

	if (!(*input))
		*input = add;
	else
	{
		lol = *input;
		while (lol->next)
			lol = lol->next;
		lol->next = add;
	}
	(*ant_go)++;
}

void	fill_tmp_input_default(t_input *input, int y)
{
	input->next = NULL;
	input->room_index = 0;
	input->patch_index = y;
}

void	clear_input(t_input *input)
{
	t_input		*tmp;

	tmp = input;
	while (input)
	{
		tmp = input;
		input = input->next;
		free(tmp);
	}
}
