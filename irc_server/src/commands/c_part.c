/*
** c_part.c for c_part in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 08:30:29 2017 Pierre Monge
** Last update Sun Jun 11 11:27:21 2017 Pierre Monge
*/

#include "command.h"
#include "channel.h"
#include "broadcast.h"
#include "client_write.h"

static int	client_is_member(t_channel *channel, t_client *client)
{
  t_membership	*ms;

  ms = client->channels->next;
  while (ms)
    {
      if (ms->channel == channel)
	return (1);
      ms = ms->next;
    }
  return (0);
}

int		command_part(t_client *client, t_client_command command)
{
  t_channel	*channel;

  if (!client->nick)
    return (client_write_buffer(client, ERR_451), 0);
  if (command.argc < 2)
    return (client_write_buffer(client, ERR_461, "PART"), 0);
  channel = hash_table_find_server(&server.channels, command.args[1]);
  if (!channel)
    return (client_write_buffer(client, ERR_403, command.args[1]), 0);
  if (!client_is_member(channel, client))
    return (client_write_buffer(client, ERR_442, command.args[1]), 0);
  client_write_buffer(client, RPL_PART, client->nick, channel->name);
  broadcast_part_channel(client, channel);
  channel_delete_user(channel, client);
  return (0);
}
