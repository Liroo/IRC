/*
** event.c for event in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue May 30 06:30:07 2017 Pierre Monge
** Last update Thu Jun  1 19:23:59 2017 Pierre Monge
*/

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "struct.h"
#include "event.h"

static int	event_read(int fd)
{
  (void)fd;
  return (0);
}

static int	event_write(int fd)
{
  (void)fd;
  return (0);
}

int		event_dispatch(t_fdset fd_event)
{
  int		fd;
  t_fd_entry	*fde;
  EVENT		event_flags;

  fd = 0;
  while (fd <= server.secure_fdset.highest_fd && fd_event.num > 0)
    {
      event_flags = 0;
      fde = &fd_entry[fd];
      if (!fde->is_open)
	FOR_ITERATION(fd);
      if (FD_ISSET(fd, &fd_event.read_fds))
	event_flags |= EVENT_READ;
      if (FD_ISSET(fd, &fd_event.write_fds))
	event_flags |= EVENT_WRITE;
      if (!event_flags)
	FOR_ITERATION(fd);
      if (event_flags & EVENT_READ && event_read(fd) == -1)
	return (-1);
      if (event_flags & EVENT_WRITE && event_write(fd) == -1)
	return (-1);
      fd++;
      fd_event.num--;
    }
  return (0);
}
