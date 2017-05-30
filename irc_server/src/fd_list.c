/*
** fd_list.c for fd_list in /Users/pierre/Epitech/PSU/IRC
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Mon May 29 14:38:58 2017 Pierre Monge
** Last update Tue May 30 06:31:57 2017 Pierre Monge
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

#include "fd_list.h"
#include "struct.h"
#include "socket.h"

 int		fd_add(int fd)
{
  t_client	*client;

  if ((fd < 0) || (fd > MAX_CONNECTIONS))
    return (-1);
  client = &server.clients[fd];
  FD_SET(fd, &server.secure_fdset.read_fds);
  if (fd > server.highest_fd)
    server.highest_fd = fd;
  client->sock.fd = fd;
  client->sock.addr_len = sizeof(client->sock.addr);
  if (getpeername(fd, (struct sockaddr *)&client->sock.addr,
		  &client->sock.addr_len) == -1)
    return (perror("getpeername"), -1);
  client->sock.is_open = 1;
  return (0);
}

int		fd_remove(int fd)
{
  t_client	*client;
  int		i;
  int		tmp;

  if ((fd < 0) || (fd > MAX_CONNECTIONS))
    return (-1);
  client = &server.clients[fd];
  if (client->sock.is_open == 0)
    return (-1);
  FD_CLR(fd, &server.secure_fdset.read_fds);
  if (fd == server.highest_fd)
    {
      i = 0;
      tmp = server.me.sock.fd;
      while (i < server.highest_fd)
	{
	  if (server.clients[i].sock.fd > tmp)
	    tmp = server.clients[i].sock.fd;
	  i++;
	}
      server.highest_fd = tmp;
    }
  bzero(client, sizeof(t_client));
  return socket_close(fd);
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
  fd_event.num = pselect(server.highest_fd + 1, &fd_event.read_fds,
			 &fd_event.write_fds, NULL, &to, &emptyset);
  if (fd_event.num < 0)
    perror("select");
  return (fd_event);
}

int		fd_accept(int sock_fd)
{
  int		fd;

  fd = accept(sock_fd, NULL, NULL);
  if (fd < 0)
    return (perror("accept"), -1);
  // TODO get hostname using `getnameinfo`
  // and gere buffer for client to answer DNS lookup
  return fd_add(fd);
}
