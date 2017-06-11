/*
** c_join.c for c_join in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 08:29:34 2017 Pierre Monge
** Last update Sun Jun 11 16:49:04 2017 Pierre Monge
*/

#include "command.h"
#include "channel.h"
#include "client_write.h"
#include "broadcast.h"

static int	client_count_channel(t_client *client)
{
  int		i;
  t_membership	*ms;

  i = 0;
  ms = client->channels->next;
  while (ms)
    {
      i++;
      ms = ms->next;
    }
  return (i);
}

static void	join_list_users(t_client *client, t_channel *channel)
{
  t_member	*member;

  member = channel->clients->next;
  client_write_buffer(client, RPL_353, client->nick,
		      channel->name, channel->name);
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

int		command_join(t_client *client, t_client_command command)
{
  t_channel	*channel;

  if (!client->nick)
    return (client_write_buffer(client, ERR_451), 0);
  if (command.argc < 2)
    return (client_write_buffer(client, ERR_461, client->nick, "JOIN"), 0);
  if (command.args[1][0] != '#')
    return (client_write_buffer(client, ERR_403, client->nick,
				command.args[1]), 0);
  if (client_count_channel(client) > 9)
    return (client_write_buffer(client, ERR_405, client->nick,
				command.args[1]), 0);
  channel = hash_table_find_channel(&server.channels, command.args[1]);
  if (!channel &&
      !(channel = channel_create(command.args[1])))
    return (-1);
  broadcast_join_channel(client, channel);
  channel_insert_user(channel, client);
  client_write_buffer(client, RPL_JOIN, client->nick, channel->name);
  client_write_buffer(client, RPL_332, client->nick,
		      channel->name, channel->name);
  join_list_users(client, channel);
  return (0);
}
