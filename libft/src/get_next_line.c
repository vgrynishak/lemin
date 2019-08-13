/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgrynish <vgrynish@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:23:40 by vgrynish          #+#    #+#             */
/*   Updated: 2018/12/08 21:13:25 by vgrynish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_gnl	*catch_fd(t_gnl **files, int fd)
{
	t_gnl	*found;
	t_gnl	*test;

	test = NULL;
	found = (*files);
	while (found)
	{
		if (found->fd == fd)
			return (found);
		test = found;
		found = found->next;
	}
	if (!(found = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	found->fd = fd;
	found->start = 0;
	found->finish = 0;
	found->next = NULL;
	if (test == NULL)
		(*files) = found;
	if (test != NULL)
		test->next = found;
	return (found);
}

static char		*ft_strj_n(char *s1, int len1, char *s2, int len2)
{
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (new == NULL)
		return (NULL);
	while (i < len1)
	{
		new[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	if (len1 != 0)
		free(s1);
	return (new);
}

int				ft_str(char *c, int len)
{
	int i;

	i = 0;
	while (c[i] != '\n' && i < len)
		i++;
	return (i);
}

static int		read_line(t_gnl **file, char **line)
{
	int k;
	int len;

	len = 0;
	while (1)
	{
		if ((*file)->finish <= (*file)->start)
		{
			(*file)->start = 0;
			(*file)->finish = read((*file)->fd, (*file)->after_n, BUFF_SIZE);
			if ((*file)->finish < 0)
				return (-1);
			if ((*file)->finish == 0)
				return ((*line != NULL));
		}
		k = (*file)->start + ft_str(&(((*file)->after_n)[(*file)->start]),
								(*file)->finish - (*file)->start);
		if ((!(*line = ft_strj_n(*line, len, &(((*file)->after_n)
								[(*file)->start]), k - (*file)->start))))
			return (-1);
		len += k - (*file)->start;
		(*file)->start = k + 1;
		if (k < (*file)->finish)
			return (1);
	}
}

int				get_next_line(const int fd, char **line)
{
	static	t_gnl	*files;
	t_gnl			*file;

	if (fd < 0 || line == NULL || !(file = catch_fd(&files, fd)))
		return (-1);
	*line = NULL;
	return (read_line(&(file), &(*line)));
}
