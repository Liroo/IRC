/*
** c_nick.c for c_nick in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 04:59:42 2017 Pierre Monge
** Last update Sun Jun 11 09:38:35 2017 Pierre Monge
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "command.h"
#include "hash.h"
#include "list.h"
#include "client_write.h"
#include "broadcast.h"

static int	validate_nick(char *nick)
{
  if (strlen(nick) > 9)
    return (1);
  if (strchr(nick, '#'))
    return (1);
  return (0);
}

int		command_nick(t_client *client, t_client_command command)
{
  char		*nick;
  t_client	*client_using_nick;
  char		*old_name;

  nick = command.args[1];
  old_name = NULL;
  if (!nick)
    return (client_write_buffer(client, ERR_431), 0);
  if (command.argc > 2 || validate_nick(nick))
    return (client_write_buffer(client, ERR_432, nick), 0);
  client_using_nick = hash_table_find_client(&server.clients, nick);
  if (client_using_nick)
    return (client_write_buffer(client, ERR_433, nick), 0);
  list_del(client->list.prev, client->list.next);
  old_name = client->nick;
  if (!(client->nick = strdup(nick)))
    return (-1);
  hash_table_insert(&server.clients, client->nick, &client->list);
  broadcast_rename_client(client, old_name);
  if (old_name)
    free(old_name);
  return (client_write_buffer(client, RPL_CMD, "NICK", nick), 0);
}
