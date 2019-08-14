#include "lemin.h"


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

void free_room(char **words)
{
	char **tmp;

	tmp = words;
	while (*tmp) {
		free(*tmp);
		tmp++;
	}

	free(words);
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
		if (*command == 1)
			lemin->start = room;
		else if (*command == 2)
			lemin->end = room;
		*command = 0;
		if (lemin->rooms) {
			room->next = lemin->rooms;
		}

		lemin->rooms = room;
	}
	else {
		lemin->error = 1;
	}
	free_room(words);
}