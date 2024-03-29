#ifndef LEMIN_H
# define LEMIN_H
#include "libft.h"

typedef struct s_room		t_room;
typedef struct s_lemin		t_lemin;
typedef struct s_lst 		t_lst;
typedef struct s_link		t_link;
typedef struct s_solution	t_solution;
typedef struct s_input		t_input;


struct			s_solution
{
	int					*len_pats;
	char				***paths;
	int					count_line;
	int 				*ants_by_path;
	char  				***result_paths;
	int 				*result_paths_len;
	int 				result_line;
	int 				*result_ants_by_path;
};


struct			s_input
{
	char *room_name;
	int patch_index;
	int room_index;
	int ant_number;
	t_input *next;
};

struct			s_lemin
{
	int					count_ant;
	t_room				*start;
	t_room				*end;
	t_lst 				*input;
	t_room				*rooms;
	int					error;
	int					show_option;
	t_solution 			*solution;
};

struct			s_room
{
	char 	*name;
	int 	distance;
	t_room  *prev;
	t_lst 	*neighbors;		// list of link
	t_room	*prev_save;
	t_room	*next_save;
	t_room  *next;
};

struct			s_link
{
	int		weight;
	t_room	*room;
};

struct         s_lst 
{
	void 		*content;
	t_lst 		*next;	
};

t_room	*ft_room_new(char *name, size_t content_size);
t_lst	*ft_lst_new(void const *content, size_t content_size);
void save_input(t_lemin *lemin, char *line);
void save_start_room(t_lemin *lemin, char *line);
void parse_data(t_lemin *lemin, char *line);
void find_one_path(t_lemin *lemin);
int find_more_path(t_lemin *lemin);
void save_conection(t_room *src, t_room *dst, int weight);
void save_path(t_lemin *lemin);
void			*lst_pop(t_lst **room);
void debug(t_lemin *lemin);
void find_best_solution(t_lemin *lemin);
int count_paths(t_lemin *lemin);
//void		compute_ants_per_path(t_solution *solution, int i);
//void		solution_add(int ant_count, t_solution *solution);
void		main_solution(int ant_count, t_solution *solution);
void sort(char ***mas, int *len_mas);
int ft_strlen_num(int *n);
void find_line(t_solution *solution, int ants);
void fill_room(char **mas, t_room *room);
void fill_mass(t_lemin *lemin, char ***mas, int *len_mas);
void show_input(t_lemin *lemin, t_solution *solution);
void minus_by_patchs(t_solution *solution);
void input_start_go(t_solution *solution, int *ant_go, t_input **input);
void delete_input(t_input **input, t_input *input_delete);
void go_one_step(t_input **input, t_lemin *lemin, t_solution *solution);
void show_start(t_lemin *lemin);
int		ft_atoi_strict(char const *str);
void save_room(t_lemin *lemin, char *line, int *command);
t_room *ft_find_room(t_room *rooms, char *name);
void save_conection(t_room *src, t_room *dst, int weight);
void save_neighbors(t_lemin *lemin, char *line);
void			*lst_del(t_lst **neighbors);
void		link_delete(t_room *src, t_room *dst);
void		split(t_lemin *lemin, t_link *link);
void		prepare_to_split(t_lemin *lemin);
t_room			*link_pop(t_room *room);
void			prepare_to_merge(t_lemin *lemin);
int is_exist(t_lst *queue, t_room *room);
void			lst_push(t_lst **head, void *data);
void add_to_queue(t_lst **queue, t_room *room);
t_room *get_min(t_lst **queue);
void find_one_path(t_lemin *lemin);
void initial_rooms(t_room *rooms);
void free_room(char **words);
void fill_tmp_input_default(t_input *input, int y);
void	add_to_input(t_input **input, t_input *add, int *ant_go);
void	clear_input(t_input *input);
int length_path(t_room *room);
void fill_solution(t_solution *solution);
void free_solution(char ***paths, int *len_mas, int *ants_by_path);
int count_paths(t_lemin *lemin);
void show_patch(t_solution *solution);
void show_ants_by_patch(t_solution *solution);
void	initial_lemin(t_lemin **lemin) ;
void check_argv(int argc, char **argv, t_lemin *lemin);

#endif
