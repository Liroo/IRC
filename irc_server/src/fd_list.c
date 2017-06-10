/*
** fd_list.c for fd_list in /Users/pierre/Epitech/PSU/IRC
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Mon May 29 14:38:58 2017 Pierre Monge
** Last update Sat Jun 10 07:03:33 2017 Pierre Monge
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include "list.h"

#include "fd_list.h"
#include "struct.h"
#include "socket.h"

t_fd_entry	fd_entry[MAX_CONNECTIONS + 1];

int		fd_add(int fd, t_client *new_client)
{
  t_fd_entry	*fde;

  if ((fd < 0) || (fd > MAX_CONNECTIONS))
    return (-1);
  fde = &fd_entry[fd];
  FD_SET(fd, &server.secure_fdset.read_fds);
  if (fd > server.secure_fdset.highest_fd)
    server.secure_fdset.highest_fd = fd;
  fde->fd = fd;
  fde->is_open = 1;
  fde->client = new_client;
  return (0);
}

int		fd_remove(int fd)
{
  t_fd_entry	*fde;
  int		i;
  int		tmp;

  if ((fd < 0) || (fd > MAX_CONNECTIONS))
    return (-1);
  fde = &fd_entry[fd];
  if (fde->is_open == 0)
    return (-1);
  FD_CLR(fd, &server.secure_fdset.read_fds);
  if (fd == server.secure_fdset.highest_fd)
    {
      i = 0;
      tmp = server.me.sock.fd;
      while (i < server.secure_fdset.highest_fd)
	{
	  if (fd_entry[i].is_open && i > tmp)
	    tmp = i;
	  i++;
	}
      server.secure_fdset.highest_fd = tmp;
    }
  bzero(fde, sizeof(t_fd_entry));
  return (0);
}

t_fdset			fd_select(time_t delay)
{
  struct timespec	to;
  t_fdset		fd_event;
  sigset_t		emptyset;

  to.tv_sec = delay / 1000;
  to.tv_nsec = (delay % 1000) * 1000 * 1000;
  memcpy(&fd_event.read_fds, &server.secure_fdset.read_fds, sizeof(fd_set));
  memcpy(&fd_event.write_fds, &server.secure_fdset.write_fds, sizeof(fd_set));
  sigemptyset(&emptyset);
  fd_event.num = pselect(server.secure_fdset.highest_fd + 1,
			 &fd_event.read_fds, &fd_event.write_fds,
			 NULL, &to, &emptyset);
  if (fd_event.num < 0)
    perror("select");
  return (fd_event);
}

int		fd_accept(int sock_fd)
{
  int		fd;
  t_client	*new_client;

  if (!(new_client = malloc(sizeof(t_client))))
    return (perror("malloc"), -1);
  bzero(new_client, sizeof(t_client));
  new_client->sock.addr_len = sizeof(new_client->sock.addr);
  fd = accept(sock_fd, (struct sockaddr *)&new_client->sock.addr,
	      (socklen_t *)&new_client->sock.addr_len);
  new_client->fd = fd;
  new_client->created_at = time(NULL);
  if (fd < 0)
    return (perror("accept"), -1);
  if (fd_add(fd, new_client) == -1)
    return (-1);
  list_add_tail(&new_client->list, &server.connection_queue);
  return (0);
}
