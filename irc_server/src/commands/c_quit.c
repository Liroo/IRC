/*
** c_quit.c for c_quit in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 05:00:26 2017 Pierre Monge
** Last update Sat Jun 10 07:05:01 2017 Pierre Monge
*/

#include <stdlib.h>

#include "command.h"
#include "fd_list.h"

int	command_quit(t_client *client, t_client_command command)
{
  (void)command;
  list_del(client->list.prev, client->list.next);
  fd_remove(client->fd);
  socket_close(client->fd);
  free(client);
  return (1);
}
