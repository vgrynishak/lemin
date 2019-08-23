/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 19:56:23 by vgrynish          #+#    #+#             */
/*   Updated: 2019/08/23 20:01:44 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	input_start_go(t_solution *solution, int *ant_go, t_input **input)
{
	char	***mas;
	int		*len_mas;
	int		y;
	char	**tmp;
	t_input	*tmp_input;

	mas = solution->result_paths;
	len_mas = solution->result_ants_by_path;
	y = 0;
	while (*mas)
	{
		if (*len_mas > 0)
		{
			tmp = *mas;
			tmp_input = (t_input *)malloc(sizeof(t_input));
			fill_tmp_input_default(tmp_input, y);
			tmp_input->room_name = *tmp;
			tmp_input->ant_number = *ant_go;
			add_to_input(input, tmp_input, ant_go);
		}
		y++;
		mas++;
		len_mas++;
	}
	minus_by_patchs(solution);
}

void	delete_input(t_input **input, t_input *input_delete)
{
	t_input *tmp;
	t_input *prev;

	tmp = *input;
	if (tmp == input_delete)
	{
		*input = tmp->next;
		free(tmp);
	}
	else
	{
		while (tmp)
		{
			if (tmp == input_delete)
			{
				prev->next = tmp->next;
				free(tmp);
				break ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	go_one_step(t_input **input, t_lemin *lemin, t_solution *solution)
{
	t_input	*tmp_input;
	t_input	*tmp;
	char	***mas;

	tmp_input = *input;
	mas = solution->result_paths;
	while (tmp_input)
	{
		tmp = tmp_input;
		tmp_input = tmp_input->next;
		if (tmp->room_name == lemin->end->name)
			delete_input(input, tmp);
		else
		{
			tmp->room_index++;
			tmp->room_name = mas[tmp->patch_index][tmp->room_index];
		}
	}
}

void	show_start(t_lemin *lemin)
{
	t_lst	*tmp;

	tmp = lemin->input;
	while (tmp)
	{
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	show_input(t_lemin *lemin, t_solution *solution)
{
	t_input	*input;
	t_input	*input_go;
	int		i;
	int		ant_go;

	ant_go = 1;
	input = NULL;
	i = 0;
	show_start(lemin);
	while (i < solution->result_line)
	{
		if (input)
			go_one_step(&input, lemin, solution);
		input_start_go(solution, &ant_go, &input);
		input_go = input;
		while (input_go)
		{
			ft_printf("L%d-%s ", input_go->ant_number, input_go->room_name);
			input_go = input_go->next;
		}
		ft_printf("\n");
		i++;
	}
	clear_input(input);
}
