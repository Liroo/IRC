/*
** event.h for event in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue May 30 06:28:44 2017 Pierre Monge
** Last update Tue May 30 08:24:12 2017 Pierre Monge
*/

#ifndef EVENT_H
# define EVENT_H

# include "fd_list.h"

# define EVENT char
# define EVENT_READ 0x1
# define EVENT_WRITE 0x2

int	event_dispatch(t_fdset fd_event);

#endif /* !EVENT_H */
