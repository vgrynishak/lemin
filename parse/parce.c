#include "lemin.h"

void save_input(t_lemin *lemin, char *line)
{
	t_lst  *input;
	t_lst 	*tmp;
	if (*line != '\0') {
		input = ft_lst_new(line, ft_strlen(line));

		if (lemin->input == NULL)
		{
			lemin->input = input;
		} else {
			tmp = lemin->input;

			while (tmp->next) {
				tmp = tmp->next;
			}

			tmp->next = input;
		}
	}
}


int		ft_atoi_strict(char const *str)
{
	int		abs;

	if (*str == '-' || *str == '+')
		++str;
	if (*str == '\0')
		return 0;
	abs = 0;
	while ('0' <= *str && *str <= '9')
	{
		abs = abs * 10 + (int)(*(str++) - '0');
		if (abs < 0 && !(abs == -2147483648 && *str == '\0'))
			return 0;
	}
	if (*str)
		return 0;

	return 1;
}

void save_room(t_lemin *lemin, char *line, int *command)
{
	char		**words;
	t_room 		*room;

	words = ft_strsplit(line, ' ');

	if (words[0] && words[1] && words[2] && !words[3] 
			&& !ft_strchr(words[0], '-')
			&& ft_atoi_strict(words[1])
			&& ft_atoi_strict(words[2]))
	{
		room = ft_room_new(words[0], ft_strlen(words[0]));

		if (*command == 1) {
			lemin->start = room;
		} else if (*command == 2) {
			lemin->end = room;
		}

		*command = 0;

		if (lemin->rooms) {
			room->next = lemin->rooms;
		}

		lemin->rooms = room;
	}
	else {
		lemin->error = 1;
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

t_room *ft_find_room(t_room *rooms, char *name) 
{
	t_room *tmp;

	tmp = rooms;

	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name)) {
			return tmp;
		}
		tmp = tmp->next;
	}

	return NULL;
}

void save_conection(t_room *src, t_room *dst, int weight)
{
	t_lst *neighbor;

	t_link 	*link;
	link = (t_link *)malloc(sizeof(t_link));

	link->room = dst;
	link->weight = weight;

	neighbor = ft_lst_new(link, sizeof(t_link));


	if (src->neighbors) {
		neighbor->next = src->neighbors;
	}

	src->neighbors = neighbor;
}

void save_neighbors(t_lemin *lemin, char *line)
{
	char		**words;
	t_room     	*first_room;
	t_room     	*second_room;
	
	words = ft_strsplit(line, '-');
	if (words[0] && words[1] && !words[2] &&
		(first_room = ft_find_room(lemin->rooms, words[0])) &&
		(second_room = ft_find_room(lemin->rooms, words[1]))		
	){
		save_conection(first_room, second_room, 1);
		save_conection(second_room, first_room, 1);
	}
	else{
		lemin->error = 1;
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
	} else 
		lemin->error = 1;	
}