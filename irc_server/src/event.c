/*
** event.c for event in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue May 30 06:30:07 2017 Pierre Monge
** Last update Tue May 30 08:31:50 2017 Pierre Monge
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
  // Todo reduce function to 25 lines or less
  int		fd;
  t_client	*client;
  EVENT		event_flags;

  fd = 0;
  while (fd < server.highest_fd && fd_event.num > 0)
    {
      event_flags = 0;
      client = &server.clients[fd];
      if (!client->sock.is_open)
	{
	  fd++;
	  continue;
	}
      if (FD_ISSET(fd, &fd_event.read_fds))
	event_flags |= EVENT_READ;
      if (FD_ISSET(fd, &fd_event.write_fds))
	event_flags |= EVENT_WRITE;
      if (!event_flags)
	{
	  fd++;
	  continue;
	}
      if (event_flags & EVENT_READ && event_read(fd) == -1)
	return (-1);
      if (event_flags & EVENT_WRITE && event_write(fd) == -1)
	return (-1);
      fd++;
      fd_event.num--;
    }
  return (0);
}
