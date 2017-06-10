/*
** event.h for event in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue May 30 06:28:44 2017 Pierre Monge
** Last update Sat Jun 10 04:57:08 2017 Pierre Monge
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

/*
** event_dispatch - dispatch event returned from select
** fd_event: multi fdset read and write to check
*/
int	event_dispatch(t_fdset fd_event);

#endif /* !EVENT_H */
