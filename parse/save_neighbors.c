#include "lemin.h"

t_room *ft_find_room(t_room *rooms, char *name) 
{
	t_room *tmp;

	tmp = rooms;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name)) 
			return tmp;
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

	free(link);
	if (src->neighbors) 
		neighbor->next = src->neighbors;
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
	else
		lemin->error = 1;
	free_room(words);
}