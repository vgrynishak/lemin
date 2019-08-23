#include "lemin.h"

int is_exist(t_lst *queue, t_room *room)
{
    t_lst *tmp_queue;

    tmp_queue = queue;
    while (tmp_queue)
    {
        if (tmp_queue->content == room)
            return 1;
        tmp_queue = tmp_queue->next;
    }
    return 0;
}

void			lst_push(t_lst **head, void *data)
{
	t_lst		*item;

	item = (t_lst *)malloc(sizeof(t_lst));
	item->content = data;
	item->next = *head;
	*head = item;
}

void add_to_queue(t_lst **queue, t_room *room)
{
    t_lst   *tmp_neighbors;
    t_link  *link;
    int     new_distance;

    tmp_neighbors = room->neighbors;
    while (tmp_neighbors)
    {
        link = tmp_neighbors->content;
        new_distance = room->distance + link->weight;
         if (new_distance < link->room->distance) {
            link->room->distance = new_distance;
            link->room->prev = room;
			if (!is_exist(*queue, link->room)) {
            	lst_push(queue, link->room);
			}
        }
        tmp_neighbors = tmp_neighbors->next;
    }
}

//void fill_var(t_lst **prev, t_room **min, t_lst **next,  )
/* 
t_room *min(t_lst **tmp_queue, t_lst *prev, t_lst *next, t_lst *tmp_prev)
{
    t_room      *min;

    while (*tmp_queue)
    {
        if (!min) {
            prev = NULL;
            min = (*tmp_queue)->content;
            next = (*tmp_queue)->next;
        }
        else if (min->distance > ((t_room * )(*tmp_queue)->content)->distance) {
            prev = tmp_prev;
            next = (*tmp_queue)->next;
            min = (*tmp_queue)->content;
        }
        tmp_prev = *tmp_queue;
        *tmp_queue = (*tmp_queue)->next;    
    }
    if (!prev) 
        *queue = next;
    else 
        prev->next = next;
    return min;
}*/

t_room *get_min(t_lst **queue)
{
    t_lst       *tmp_queue;
    t_lst       *prev;
    t_room      *min;
    t_lst       *tmp_prev;
    t_lst       *next;

    min = NULL;
    if (!(*queue)) 
        return NULL;
    tmp_queue = *queue;
    while (tmp_queue)
    {
        if (!min) {
            prev = NULL;
            min = tmp_queue->content;
            next = tmp_queue->next;
        }
        else if (min->distance > ((t_room * )tmp_queue->content)->distance) {
            prev = tmp_prev;
            next = tmp_queue->next;
            min = tmp_queue->content;
        }
        tmp_prev = tmp_queue;
        tmp_queue = tmp_queue->next;    
    }
    if (!prev){
        free(*queue);
        *queue = next;
    }
    else{
        free(prev->next);
        prev->next = next;
    }
    return min;
}

void find_one_path(t_lemin *lemin) 
{
    t_lst *queue;
    t_room *src;

    src = lemin->start;
    queue = NULL;
    initial_rooms(lemin->rooms);
    lemin->start->distance = 0;
    while (src && src != lemin->end)
    {
        add_to_queue(&queue, src);
        src = get_min(&queue);
//        ft_printf("s\n");
    }

    //t_lst = *l;
    while (queue) {
        free(queue);
        queue = queue->next;
    }
		//system("leaks -q lem-in >&2");
}