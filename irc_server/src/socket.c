/*
** socket.c for socket in /Users/pierre/Epitech/PSU/IRC
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun May 28 16:15:46 2017 Pierre Monge
** Last update Sat Jun 10 04:19:40 2017 Pierre Monge
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include "struct.h"
#include "socket.h"
#include "fd_list.h"
#include "event.h"

int			socket_open(t_socket_info *socket_info,
				    unsigned int port)
{
  struct protoent	*protocol;
  int			option_value;

  if (!(protocol = getprotobyname(PROTOTYPE_NAME)))
    return (fprintf(stderr, "getprotobyname"), -1);
  if ((socket_info->fd = socket(AF_INET, SOCK_STREAM, protocol->p_proto)) <= 1)
    return (perror("socket"), -1);
  option_value = 1;
  if (setsockopt(socket_info->fd, SOL_SOCKET,
		 SO_REUSEADDR, &option_value, sizeof(int)) == -1)
    perror("setsockopt");
  socket_info->addr.sin_family = AF_INET;
  socket_info->addr.sin_port = htons(port);
  socket_info->addr.sin_addr.s_addr = INADDR_ANY;
  socket_info->addr_len = sizeof(socket_info->addr);
  if (bind(socket_info->fd, (const struct sockaddr*)&socket_info->addr,
	   socket_info->addr_len) == -1)
    return (perror("bind"), socket_close(socket_info->fd), -1);
  if (listen(socket_info->fd, MAX_CONNECTIONS) == -1)
    return (perror("listen"), socket_close(socket_info->fd), -1);
  return (0);
}

int	socket_close(int socket_fd)
{
  if (close(socket_fd) == -1)
    {
      perror("socket_close");
      return (-1);
    }

  return (0);
}

char		*socket_get_ip(t_socket_info socket_info)
{
  char		*str;

  if ((str = malloc(INET_ADDRSTRLEN)) == NULL)
    return (NULL);
  inet_ntop( AF_INET, &socket_info.addr.sin_addr, str, INET_ADDRSTRLEN );
  return (str);
}

int		socket_loop()
{
  t_fdset	fd_event;

  while (!server.sig_handled)
    {
      fd_event = fd_select(60000);
      if (server.sig_handled)
	break;
      if (fd_event.num == -1)
	return (-1);
      if (fd_event.num == 0)
	continue;
      if (FD_ISSET(server.me.sock.fd, &fd_event.read_fds))
	{
	  if (fd_accept(server.me.sock.fd) == -1)
	    return (-1);
	  fd_event.num--;
	}
      if (event_dispatch(fd_event) == -1)
	return (-1);
      // TODO PING test based on time ?
    }
  return (0);
}
