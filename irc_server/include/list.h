/*
** list.h for list in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun  1 06:11:17 2017 Pierre Monge
** Last update Thu Jun  1 07:58:58 2017 Pierre Monge
*/

#ifndef LIST_H
# define LIST_H

/*
** This is a kernel implementation set to the epitech norm
** We don't have access to kernel includes using global include "<" ">"
** this is why I decided to recode the list.h simplified
** and to use them for our projects
**
** This is a really basic implementation based on linux/list.h
**
** -- Pierre
*/

/*
** ps: removing macro multiline remove the only set a polymorphism stuff
** we should learn... Thx norm
*/

typedef struct s_list_head	t_list_head;
struct		s_list_head
{
  struct	s_list_head *next;
  struct	s_list_head *prev;
};

/*
** Returning the t_list_head element is usefull
** when the t_list_head is the first element of the structure
** It permit to cast the structure to a bigger struct
** which is sort of a container
*/
t_list_head	*list_init(t_list_head *list);
t_list_head	*list_add(t_list_head *new,
			  t_list_head *prev,
			  t_list_head *next);
t_list_head	*list_del(t_list_head *prev,
			  t_list_head *next);

static inline t_list_head	*list_add_tail(t_list_head *new,
					       t_list_head *head)
{
  return (list_add(new, head->prev, head));
}

static inline int	list_is_last(const t_list_head *list,
				     const t_list_head *head)
{
  return (list->next == head);
}

static inline int list_empty(const t_list_head *head)
{
  return (head->next == head);
}

#endif /* !LIST_H */
