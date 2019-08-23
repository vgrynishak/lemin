#include "lemin.h"

t_room	*ft_room_new(char *name, size_t content_size)
{
	t_room *p;

	p = NULL;
	p = (t_room *)malloc(sizeof(t_room));
	if (p == NULL)
		return (NULL);
	if (name == NULL || content_size == 0)
		p->name = NULL;
	else if ((p->name = (char *)malloc(content_size + 1)))
		ft_memcpy(p->name, name, content_size);
	else
	{
		free(p);
		p = NULL;	// should return here
	}
	p->next = NULL;
	p->neighbors = NULL;
	p->distance = 1000000;
	p->next_save = NULL;
	p->prev_save = NULL;
	p->prev = NULL;
	return (p);
}

t_lst	*ft_lst_new(void const *content, size_t content_size)
{
	t_lst *p;

	p = NULL;
	p = (t_lst *)malloc(sizeof(t_lst));
	if (p == NULL)
		return (NULL);
	if (content == NULL || content_size == 0) {
		p->content = NULL;
	} else if ((p->content = (void *)malloc(content_size))) {
		ft_memcpy(p->content, content, content_size);
	} else {
		free(p);
		p = NULL;
	}

	p->next = NULL;
	return (p);
}

