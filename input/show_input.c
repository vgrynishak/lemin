#include "lemin.h"

void minus_by_patchs(t_solution *solution)
{
	int *tre = solution->result_ants_by_path;
	
	while (*tre)
	{
		//ft_printf("was: %d\n", *tre);
		*tre -= 1;
		//ft_printf("stay: %d\n", *tre);
	//system("leaks -q lem-in >&2");
		tre++;
	}

}

void input_start_go(t_solution *solution, int *ant_go, t_input **input)
{
	//ft_printf("gere\n");
	char ***mas;
	int *len_mas;
	mas = solution->result_paths;
	len_mas = solution->result_ants_by_path;

//ft_printf
	int y = 0;
	while (*mas)
	{
		if (*len_mas > 0) {
			char **tmp;
			tmp = *mas;
			
			t_input *tmp_input;
			tmp_input = (t_input *)malloc(sizeof(t_input));
			tmp_input->room_name = *tmp;
			tmp_input->room_index = 0;
			tmp_input->patch_index  = y;
			tmp_input->ant_number = *ant_go;
			tmp_input->next = NULL;
			if (!(*input)) { 
				*input = tmp_input;
			} else {
				t_input *lol;
				lol = *input;
				while(lol->next) {
					lol = lol->next;
				}
				lol->next = tmp_input;
			}
			
			(*ant_go)++;
		}
		y++;
		mas++;
		len_mas++;
	}
	//system("leaks -q lem-in >&2");
	//	ft_printf("__________________________________-\n");
	minus_by_patchs(solution);
	//system("leaks -q lem-in >&2");
	//	ft_printf("__________________________________-\n");exit(1);
}

void delete_input(t_input **input, t_input *input_delete)
{
	t_input *tmp;
	t_input *prev;

	tmp = *input;

	if (*input == input_delete) {
		*input = (*input)->next;
		free(tmp);
	} else {
		while (tmp)
		{
			if (tmp == input_delete) {
				free(prev->next);
				prev->next = tmp->next;
				break;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void go_one_step(t_input **input, t_lemin *lemin, t_solution *solution)
{
	t_input *tmp_input;

	tmp_input = *input;
	char ***mas;
	mas = solution->result_paths;

	while (tmp_input)
	{
		if (tmp_input->room_name == lemin->end->name) {
			delete_input(input, tmp_input);
		} else {
			 tmp_input->room_index++;
			 tmp_input->room_name = mas[tmp_input->patch_index][tmp_input->room_index];
		}
		
		tmp_input = tmp_input->next;
	}
	
}

void show_start(t_lemin *lemin)
{
    t_lst  *tmp;

	tmp = lemin->input;
	while (tmp) {
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
    ft_printf("\n");
}

void show_input(t_lemin *lemin)
{
    t_solution *solution = lemin->solution;
    t_input *input;
	t_input *input_go;
	int ant_go = 1;
	input = NULL;
	int i = 0; 
    //show_start(lemin);
//	system("leaks -q lem-in >&2");exit(1);

	while (i < solution->result_line)
	{
		//ft_printf("%d\n", i);
		if (input)
			go_one_step(&input, lemin, solution);
		input_start_go(solution, &ant_go, &input);
		//system("leaks -q lem-in >&2");
		//ft_printf("__________________________________-\n");
		input_go = input;

		while (input_go)
		{
			ft_printf("L%d-%s ", input_go->ant_number, input_go->room_name);
			input_go = input_go->next;
		}
		ft_printf("\n");
		i++;
		//system("leaks -q lem-in >&2");
		//ft_printf("__________________________________-\n");
	}
//	system("leaks -q lem-in >&2");
	//free(input->room_name);
	free(input);
	free(input_go);
	//system("leaks -q lem-in >&2");exit(1);

}