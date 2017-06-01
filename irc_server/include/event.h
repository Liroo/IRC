/*
** event.h for event in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue May 30 06:28:44 2017 Pierre Monge
** Last update Thu Jun  1 11:35:54 2017 Pierre Monge
*/

#ifndef EVENT_H
# define EVENT_H

# include "fd_list.h"

# define EVENT char
# define EVENT_READ 0x1
# define EVENT_WRITE 0x2

/*
** This macro is not lovely, I know
** This is a fake for loop using iteration + continue
** to re-invent the for/goto looping
**
** I did not like it but I have to.
** The other way was to split the event_dispatch loop
** in two function and this is horible to read...
*/
# define FOR_ITERATION(it) it = it + 1; continue;

int	event_dispatch(t_fdset fd_event);

#endif /* !EVENT_H */
