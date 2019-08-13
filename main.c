#include "lemin.h"

void initial_lemin(t_lemin **lemin) 
{
	*lemin = (t_lemin *)malloc(sizeof(t_lemin));
	
	(*lemin)->input = NULL;
	(*lemin)->count_ant = 0;
	(*lemin)->start = NULL;
	(*lemin)->end = NULL;
	(*lemin)->rooms = NULL;
	(*lemin)->error = 0;
	
}

void show(t_link *link)
{
	t_room *room;
	room = link->room;

	ft_printf("The path: ");			//
	while (room) {							//
		ft_printf("%s ", room->name);		//
		ft_printf("(%s ", room->prev_save ? room->prev_save->name : "-");		//
		ft_printf("%s) ", room->next_save ? room->next_save->name : "-");		//
		room = room->prev_save;					//
	}									//
	ft_printf("\n");
}
/* 
int count_paths(t_lemin *lemin) {
	int		count;
	t_lst	*neighbors;

	count = 0;
	neighbors = lemin->end->neighbors;
	while (neighbors) {
		if (((t_link *)neighbors->content)->room->next_save == lemin->end) {
			++count;	
		}
		neighbors = neighbors->next;
	}
	return count;
}
*/
/* int length_path(t_room *room)
{
	int n = 0;

	while (room)
	{
		n++;
		room = room->next_save;
	}
	
	return n;
}

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

void fill_mass(t_lemin *lemin, char ***mas, int *len_mas)
{
	t_lst *neighbors;
	char **path;
	t_room *room;
	int n;
	int i = 0;
	//ft_printf("( ");
	neighbors = lemin->start->neighbors;
	while (neighbors) {
		room = ((t_link *)neighbors->content)->room;
		if (room->prev_save == lemin->start) {
			n = length_path(room);
			mas[i] = (char **)malloc(sizeof(char *) * (n + 1));
			len_mas[i] = n;
			fill_room(mas[i], room);
			i++;
			//ft_printf("%d ", n);
		}
		neighbors = neighbors->next;
	}
	len_mas[i] = 0;
	mas[i] = NULL;
	//ft_printf(")\n");
}


void sort(char ***mas, int *len_mas)
{
	int i = 0;
	int j;
	int tmp;
	char **tmp_mas;
	while (len_mas[i])
	{
		j = i + 1;
		while (len_mas[j])
		{
			if (len_mas[j] < len_mas[i])
			{
				tmp = len_mas[i];
				len_mas[i] = len_mas[j];
				len_mas[j] = tmp;
				tmp_mas = mas[i];
				mas[i] = mas[j];
				mas[j] = tmp_mas;
			}
			j++;
		}
		i++;		
	}
	
}

int ft_strlen_num(int *n)
{
	int i = 0;

	while (*n) {
		i++;
		n++;
	}

	return i;
}

static void		compute_ants_per_path(t_solution *solution, int i)
{
	int			j;

	j = 0;
	 while (j < i)
	{
		solution->ants_by_path[j] = solution->count_line - solution->len_pats[j] + 1;
		++j;
	}
	while (j < ft_strlen_num(solution->len_pats))
	{
		solution->ants_by_path[j] = 0;
		++j;
	}
}

static void		solution_add(int ant_count, t_solution *solution)
{
	int			i;

	solution->count_line += 1;
	i = 0;
	while (ant_count--)
	{
		solution->ants_by_path[i]++;
		++i;
	}
}

void		main_solution(int ant_count, t_solution *solution)
{
	int			i;
	int			d;
	int n_turns;

	int *len_mas = solution->len_pats;
	i = 1;
	while (i < ft_strlen_num(len_mas))
	{
		d = len_mas[i] - len_mas[i - 1];
		if (ant_count / i <= d)
			break ;
		ant_count -= d * i;
		++i;
	}
	d = ant_count / i;
	ant_count -= d * i;
	solution->count_line = len_mas[i - 1] + d - 1;
	compute_ants_per_path(solution, i);
	if (ant_count > 0)
		solution_add(ant_count, solution);	
}

void find_line(t_solution *solution, int ants)
{
	sort(solution->paths, solution->len_pats);
	main_solution(ants, solution);
}

void minus_by_patchs(t_solution *solution)
{
	int *tre = solution->result_ants_by_path;
	while (*tre)
	{
		(*tre)--;
		tre++;
	}
}

void input_start_go(t_solution *solution, int *ant_go, t_input **input)
{
	char ***mas;
	int *len_mas;
	mas = solution->result_paths;
	len_mas = solution->result_ants_by_path;

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
	minus_by_patchs(solution);	
}

void delete_input(t_input **input, t_input *input_delete)
{
	t_input *tmp;
	t_input *prev;

	tmp = *input;

	if (*input == input_delete) {
		*input = (*input)->next;
	} else {
		while (tmp)
		{
			if (tmp == input_delete) {
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
	t_input *tmp_input_save;
	t_input *prev;
	prev = NULL;
	tmp_input = *input;
	tmp_input_save = tmp_input;
	char ***mas;
	mas = solution->result_paths;
	while (tmp_input)
	{
		if (tmp_input->room_name == lemin->end->name) {
			delete_input(input, tmp_input);
			//if (!prev) {
			//ft_printf("1");
			//*input = tmp_input->next;
			//} else {
			//ft_printf("2");
			//	prev->next = tmp_input->next;
				//*input = tmp_input_save;
			
		} else {
			 tmp_input->room_index++;
			 tmp_input->room_name = mas[tmp_input->patch_index][tmp_input->room_index];
		}
		
		prev = tmp_input;
		tmp_input = tmp_input->next;
	}
	
}*/
int main(void)
{

	t_lemin *lemin;

	//int fd = open("gen-maps/big/1.map", O_RDONLY);
	int fd = open("gen-maps/big-superposition/6.map", O_RDONLY);
	//int fd = open("gen-maps/big/3.map", O_RDONLY);
	//int fd = open("gen-maps/big/4.map", O_RDONLY);
	//int fd = open("gen-maps/big/5.map", O_RDONLY);
	//int fd = open("gen-maps/big/6.map", O_RDONLY);
	//int fd = open("gen-maps/big/7.map", O_RDONLY);
	//int fd = open("gen-maps/big/8.map", O_RDONLY);
	//int fd = open("gen-maps/big/9.map", O_RDONLY);
	//int fd = open("lem_in/_maps/theta_unequal_4.map", O_RDONLY);
	char *line;

	initial_lemin(&lemin);

	int i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		save_input(lemin, line);
		parse_data(lemin, line);

		if (lemin->error) {
			write(1, "ERROR\n", 6);
			ft_printf("%s\n", line);
			return 1;
		}
	}
	char ***mas;
	int *len_mas;
	//find_one_path(lemin);
	//debug(lemin);exit(1);
    //save_path(lemin);
/* 	
	int g;
	char ***mas;
	int *len_mas;
	t_solution *solution;
	solution = (t_solution *)malloc(sizeof(t_solution));
	solution->result_paths = NULL;
	solution->result_paths_len = 0;
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
*/

	find_best_solution(lemin);

	show_input(lemin);exit(1);
	t_solution *solution = lemin->solution;
	/* int *tre = solution->result_ants_by_path;
	while (*tre)
	{
		ft_printf("%d\n", *tre);
		tre++;
	}
	exit(1);*/
	t_input *input;
	t_input *input_go;
	int ant_go = 1;
	input = NULL;
	i = 0; 
	while (i < solution->result_line)
	{
		if (!input) {
			input = (t_input *)malloc(sizeof(t_input));
			input = NULL;
			input_start_go(solution, &ant_go, &input);
		} else {
			go_one_step(&input, lemin, solution);
			input_start_go(solution, &ant_go, &input);
		}
		input_go = input;

		while (input_go)
		{
			ft_printf("L%d-%s ", input_go->ant_number, input_go->room_name);
			input_go = input_go->next;
		}
		ft_printf("\n");
		/* int *tre = solution->result_ants_by_path;
		while (*tre)
		{
			ft_printf("%d\n", *tre);
			tre++;
		}*/
//		exit(1);
		i++;
	}
	
	//ft_printf("%d\n", solution->result_line);
	//exit(1);
	mas = solution->result_paths;
	len_mas = solution->result_ants_by_path;

	while (*mas)
	{
		 char **tmp;
		tmp = *mas;
		while (*tmp)
		{
			ft_printf("%s ", *tmp);
			tmp++;
		}
		ft_printf("\n");
		ft_printf("len %d\n", *len_mas);
		mas++;
		len_mas++;
	}
	
	exit(1);
	find_more_path(lemin);
	

							
/* 	t_lst *neighbors;
	t_link *l;

	neighbors = lemin->end->neighbors;
	while (neighbors)
	{
		l = neighbors->content;
		ft_printf("%s\n", l->room->prev_save->name);
		neighbors = neighbors->next;
		if (l->room->next_save == lemin->end)
			show(l);
	}exit(1);*/
	// print the path from end to start:	//	TEST
	{										//
		ft_printf("The path: ");			//
		t_room *t = lemin->end;				//
		while (t) {							//
			ft_printf("%s ", t->name);		//
			ft_printf("(%s ", t->prev_save ? t->prev_save->name : "-");		//
			ft_printf("%s) ", t->next_save ? t->next_save->name : "-");		//
			t = t->prev;					//
		}									//
		ft_printf("\n");					//
	}										//

/* 
	t_lst *ngb = lemin->start->neighbors;

	 while (ngb)
	{
		ft_printf("%s\n",((t_link *)ngb->content)->room->name );
		t_lst *tmp = ((t_link *)ngb->content)->room->neighbors;
		ft_putstr("neighbors: ");
		while (tmp)
		{
			ft_printf("%s\n",((t_link *)tmp->content)->room->name );
			tmp = tmp->next;
		}
		write (1, "\n", 1);
		ngb = ngb->next;
	}exit(1);
	 
	write(1, "input\n", 6);

	t_lst  *tmp1;

	tmp1 = lemin->input;
	while (tmp1) {
		ft_printf("%s\n", tmp1->content);
		tmp1 = tmp1->next;
	}

	write(1, "room\n", 5);
	t_room  *tmp2;

	tmp2 = lemin->rooms;

	while (tmp2) {
		ft_printf("%s\n", tmp2->name);
		tmp2= tmp2->next;
	}

	write(1, "connect\n", 8);
	t_room  *tmp3;

	tmp3 = lemin->rooms;

	while (tmp3) {
		t_lst *links;
		
		ft_printf("%s: ", tmp3->name);
		
		links = tmp3->neighbors;
		while (links)
		{
			ft_printf("%s [", ((t_link *)(links->content))->room->name);
			t_lst *tmp =((t_link *)(links->content))->room->neighbors;
			while (tmp)
			{
				ft_printf("%s ", ((t_link *)(tmp->content))->room->name);
				tmp = tmp->next;
			}
			ft_printf("] ");
			links = links->next;
		}
		
		ft_printf("\n");
		tmp3= tmp3->next;
	}*/
	return (0);
}
