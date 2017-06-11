/*
** c_quit.c for c_quit in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 05:00:26 2017 Pierre Monge
** Last update Sun Jun 11 11:05:03 2017 Pierre Monge
*/

#include <stdlib.h>

#include "command.h"
#include "channel.h"
#include "broadcast.h"

static void	client_leave_channel(t_client *client)
{
  t_membership	*channel;
  t_membership	*next;

  channel = client->channels;
  while (channel)
    {
      next = channel->next;
      if (channel->channel)
	{
	  broadcast_part_channel(client, channel->channel);
	  channel_delete_user(channel->channel, client);
	}
      channel = next;
    }
}

int	command_quit(t_client *client, t_client_command command)
{
  (void)command;
  if (client->nick)
    free(client->nick);
  list_del(client->list.prev, client->list.next);
  FD_CLR(client->fd, &server.secure_fdset.write_fds);
  fd_remove(client->fd);
  socket_close(client->fd);
  client_leave_channel(client);
  free(client);
  return (1);
}
