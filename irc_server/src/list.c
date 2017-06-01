/*
** list.c for list in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun  1 06:32:25 2017 Pierre Monge
** Last update Thu Jun  1 07:59:16 2017 Pierre Monge
*/

#include "list.h"

t_list_head	*list_init(t_list_head *list)
{
  list->next = list;
  list->prev = list;
  return (list);
}

t_list_head	*list_add(t_list_head *new,
			  t_list_head *prev,
			  t_list_head *next)
{
  next->prev = new;
  new->next = next;
  new->prev = prev;
  prev->next = new;
  return (new);
}

t_list_head	*list_del(t_list_head *prev,
			  t_list_head *next)
{
  next->prev = prev;
  prev->next = next;
  return (prev);
}
