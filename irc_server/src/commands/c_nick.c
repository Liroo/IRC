/*
** c_nick.c for c_nick in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 04:59:42 2017 Pierre Monge
** Last update Sun Jun 11 03:46:02 2017 Pierre Monge
*/

#include <stdio.h>
#include <string.h>

#include "command.h"
#include "hash.h"
#include "list.h"
#include "client_write.h"

int		command_nick(t_client *client, t_client_command command)
{
  char		*nick;
  t_client	*client_using_nick;

  nick = command.args[1];
  if (!nick)
    return (client_write_buffer(client, ERR_431), 0);
  if (strlen(nick) > 9)
    return (client_write_buffer(client, ERR_432, nick), 0);
  client_using_nick = hash_table_find_client(&server.clients, nick);
  if (client_using_nick)
    return (client_write_buffer(client, ERR_433, nick), 0);
  // rename propagation on channels
  list_del(client->list.prev, client->list.next);
  if (!(client->nick = strdup(nick)))
    return (-1);
  hash_table_insert(&server.clients, client->nick, &client->list);
  return (client_write_buffer(client, RPL_NICK, nick), 0);
}
