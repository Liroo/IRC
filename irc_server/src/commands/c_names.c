/*
** c_names.c for c_names in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 08:30:16 2017 Pierre Monge
** Last update Sun Jun 11 16:49:53 2017 Pierre Monge
*/

#include "command.h"
#include "client_write.h"

static void	names_list_users(t_client *client, t_channel *channel)
{
  t_member	*member;

  member = channel->clients->next;
  client_write_buffer(client, RPL_353, client->nick,
		      channel->name);
  while (member)
    {
      client_write_buffer(client, member->client->nick);
      if (member->next)
	client_write_buffer(client, " ");
      member = member->next;
    }
  client_write_buffer(client, CR_LF);
  client_write_buffer(client, RPL_366, client->nick, channel->name);
}

int	command_names(t_client *client, t_client_command command)
{
  t_channel	*channel;

  if (!client->nick)
    return (client_write_buffer(client, ERR_451), 0);
  if (command.argc < 2)
    return (client_write_buffer(client, ERR_461, client->nick, "NAMES"), 0);
  channel = hash_table_find_channel(&server.channels, command.args[1]);
  if (!channel)
    return (client_write_buffer(client, ERR_403, client->nick,
				command.args[1]), 0);
  names_list_users(client, channel);
  return (0);
}
