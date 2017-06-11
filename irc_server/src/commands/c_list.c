/*
** c_list.c for c_list in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 08:30:06 2017 Pierre Monge
** Last update Sun Jun 11 16:40:00 2017 Pierre Monge
*/

#include <string.h>

#include "command.h"
#include "list.h"
#include "client_write.h"

static void	list_get_channel(t_client *client, char *sstr)
{
  t_channel	*channel;
  t_list_head	*head;
  t_list_head	*pos;
  int		i;

  i = 0;
  client_write_buffer(client, RPL_321, client->nick);
  while (i < HASH_TABLE_SIZE)
    {
      head = &server.channels.table[i].list;
      pos = list_get_first(head);
      while (pos != head)
	{
	  channel = list_entry(pos, t_channel, list);
	  if (!sstr || (sstr && strcasestr(channel->name, sstr)))
	    client_write_buffer(client, RPL_322, client->nick, channel->name,
				channel->clients_size, channel->name);
	  pos = pos->next;
	}
      i++;
    }
  client_write_buffer(client, RPL_323, client->nick);
}

int		command_list(t_client *client, t_client_command command)
{
  if (!client->nick)
    return (client_write_buffer(client, ERR_451), 0);
  list_get_channel(client, command.args[1]);
  return (0);
}
