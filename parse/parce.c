#include "lemin.h"

void save_input(t_lemin *lemin, char *line)
{
	t_lst  *input;
	t_lst 	*tmp;

	if (*line != '\0') {
		input = ft_lst_new(line, ft_strlen(line));

		if (lemin->input == NULL)
			lemin->input = input;
		else {
			tmp = lemin->input;

			while (tmp->next) {
				tmp = tmp->next;
			}

			tmp->next = input;
		}
	}
}


void command(t_lemin *lemin, char *line, int *comand)
{
	if ((!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end")) && *comand)
		lemin->error = 1;
	else if (!ft_strcmp(line, "##start"))
		(*comand) = 1;
	else if (!ft_strcmp(line, "##end")) {
		(*comand) = 2;
	}
}

void parse_data(t_lemin *lemin, char *line) 
{
	static int comand = 0;
	static int allow_room = 1;
	static int allow_number = 1;

	if (line[0] == '#') {
		command(lemin, line, &comand);
	} else if ((!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end") || ft_strchr(line, ' ')) && !allow_room) {
		ft_printf("1");
		lemin->error = 1;
	} else if (line[0] == 'L')
		lemin->error = 1;
	else if (ft_strchr(line, ' ') && line[0] != ' ')
		save_room(lemin, line, &comand);
	else if (ft_strchr(line, '-')){
		allow_room = 0;
		save_neighbors(lemin, line);
	}
	else if (line[0] >= '1' && line[0] <= '9' && allow_number) {
		if (!ft_atoi_strict(line)) 
			lemin->error = 1;
		lemin->count_ant = ft_atoi(line);	
		allow_number = 0;
	} else{
		lemin->error = 1;
	}	
}