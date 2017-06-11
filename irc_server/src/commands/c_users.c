/*
** c_users.c for users in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 03:22:27 2017 Pierre Monge
** Last update Sun Jun 11 07:49:32 2017 Pierre Monge
*/

#include "command.h"
#include "client_write.h"

#include "hash.h"

static void	print_client_nick(t_client *client, t_hash_entry *entry)
{
  t_list_head	*head;
  t_list_head	*pos;
  t_client	*client_pos;

  head = &entry->list;
  pos = list_get_first(head);
  while (pos != head)
    {
      client_pos = list_entry(pos, t_client, list);
      client_write_buffer(client, RPL_393, client_pos->nick);
      pos = pos->next;
    }
}

int	command_users(t_client *client, t_client_command command)
{
  int		i;

  (void)command;
  i = 0;
  if (!client->nick)
    return (client_write_buffer(client, ERR_451), 0);
  client_write_buffer(client, RPL_392);
  while (i < HASH_TABLE_SIZE)
    {
      print_client_nick(client, &server.clients.table[i]);
      i++;
    }
  client_write_buffer(client, RPL_394);
  return (0);
}
