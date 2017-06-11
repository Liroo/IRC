/*
** c_privmsg.c for privmsg in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 05:10:24 2017 Pierre Monge
** Last update Sun Jun 11 13:41:51 2017 Pierre Monge
*/

#include "command.h"
#include "client_write.h"
#include "broadcast.h"
#include "hash.h"

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

void		privmsg_channel(t_client *client, char *name_receiver,
				char *message)
{
  t_channel	*channel;

  if (!(channel = hash_table_find_channel(&server.channels, name_receiver)))
    return (client_write_buffer(client, ERR_401, name_receiver));
  if (!client_is_member(channel, client))
    return (client_write_buffer(client, ERR_404, name_receiver));
  broadcast_message_channel(client, channel, message);
}

void		privmsg_client(t_client *client, char *nick_receiver,
			       char *message)
{
  t_client	*client_remote;

  if (!(client_remote =
	hash_table_find_client(&server.clients, nick_receiver)))
    return (client_write_buffer(client, ERR_401, nick_receiver));
  return (client_write_buffer(client_remote, RPL_PRIVMSG,
			      client->nick, client->nick, message));
}

int		command_privmsg(t_client *client, t_client_command command)
{


  if (!client->nick)
    return (client_write_buffer(client, ERR_451), 0);
  if (command.argc < 2)
    return (client_write_buffer(client, ERR_411, "PRIVMSG"), 0);
  if (command.argc < 3)
    return (client_write_buffer(client, ERR_412), 0);
  if (command.args[1][0] != '#')
    privmsg_client(client, command.args[1], command.args[2]);
  else
    privmsg_channel(client, command.args[1], command.args[2]);
  return (0);
}
