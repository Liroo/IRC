/*
** event.c for event in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Tue May 30 06:30:07 2017 Pierre Monge
** Last update Sun Jun 11 03:59:43 2017 Pierre Monge
*/

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include "struct.h"
#include "event.h"
#include "fd_list.h"
#include "parse.h"
#include "command.h"
#include "client_write.h"

static int	event_read(int fd)
{
  t_client	*client;

  client = fd_entry[fd].client;
  if (!client)
    return (0);
  if (ring_buffer_read(&client->read_buffer, fd) <= 0)
    return (command_quit(client, (t_client_command){{0}, 0, {0}}));
  client->read_buffer.offset = 0;
  if (parse_buffer_to_token(client) == -1)
    return (command_quit(client, (t_client_command){{0}, 0, {0}}));
  return (0);
}

static int	event_write(int fd)
{
  t_client	*client;

  client = fd_entry[fd].client;
  if (!client)
    return (0);
  if (client_write_once(client) == -1)
    return (command_quit(client, (t_client_command){{0}, 0, {0}}));
  return (0);
}

static EVENT	event_get_flags(int fd, t_fdset fd_event)
{
  EVENT		event_flags;

  event_flags = 0;
  if (FD_ISSET(fd, &fd_event.read_fds))
    event_flags |= EVENT_READ;
  if (FD_ISSET(fd, &fd_event.write_fds))
    event_flags |= EVENT_WRITE;
  return (event_flags);
}

int		event_dispatch(t_fdset fd_event)
{
  int		fd;
  t_fd_entry	*fde;
  EVENT		event_flags;

  fd = 0;
  while (fd <= server.secure_fdset.highest_fd && fd_event.num > 0)
    {
      fde = &fd_entry[fd];
      if (!fde->is_open ||
	  !(event_flags = event_get_flags(fd, fd_event)))
	{
	  fd++;
	  continue;
	}
      if ((event_flags & EVENT_READ) && (event_read(fd) == -1))
	return (-1);
      if ((event_flags & EVENT_WRITE) && (event_write(fd) == -1))
	return (-1);
      fd++;
      fd_event.num--;
    }
  return (0);
}
