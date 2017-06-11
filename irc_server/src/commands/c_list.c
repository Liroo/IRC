/*
** c_list.c for c_list in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 08:30:06 2017 Pierre Monge
** Last update Sun Jun 11 13:04:17 2017 Pierre Monge
*/

#include <string.h>

#include "command.h"
#include "list.h"
#include "client_write.h"

int		command_list(t_client *client, t_client_command command)
{
  t_channel	*channel;
  t_list_head	*head;
  t_list_head	*pos;
  int		i;
  char		*sstr;

  if (!client->nick)
    return (client_write_buffer(client, ERR_451), 0);
  i = 0;
  sstr = command.args[1];
  client_write_buffer(client, RPL_321);
  while (i < HASH_TABLE_SIZE)
    {
      head = &server.channels.table[i].list;
      pos = list_get_first(head);
      while (pos != head)
	{
	  channel = list_entry(pos, t_channel, list);
	  if (!sstr || (sstr && strcasestr(channel->name, sstr)))
	    client_write_buffer(client, RPL_322, channel->name,
				channel->clients_size, channel->name);
	  pos = pos->next;
	}
      i++;
    }
  client_write_buffer(client, RPL_323);
  return (0);
}
