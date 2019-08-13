#include "lemin.h"


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

void find_line(t_solution *solution, int ants)
{
	sort(solution->paths, solution->len_pats);
	main_solution(ants, solution);
}