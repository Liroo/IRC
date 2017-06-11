/*
** broadcast.c for broadcast in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 08:57:07 2017 Pierre Monge
** Last update Sun Jun 11 13:30:48 2017 Pierre Monge
*/

#include "broadcast.h"
#include "command.h"
#include "client_write.h"

void	broadcast_message_channel(t_client *client, t_channel *channel,
				  char *message)
{
  t_member	*member;

  member = channel->clients->next;
  while (member)
    {
      if (member->client != client)
	client_write_buffer(member->client, RPL_PRIVMSG, client->nick,
			    client->nick, message);
      member = member->next;
    }
}

void		broadcast_join_channel(t_client *client, t_channel *channel)
{
  t_member	*member;

  member = channel->clients->next;
  while (member)
    {
      if (member->client != client)
	client_write_buffer(member->client, RPL_JOIN, client->nick, channel->name);
      member = member->next;
    }
}

void	broadcast_part_channel(t_client *client, t_channel *channel)
{
    t_member	*member;

  member = channel->clients->next;
  while (member)
    {
      if (member->client != client)
	client_write_buffer(member->client, RPL_PART, client->nick, channel->name);
      member = member->next;
    }
}

void		broadcast_rename_client(t_client *client, char *old_name)
{
  t_membership	*ms;
  t_member	*member;

  ms = client->channels->next;
  if (!old_name)
    return ;
  while (ms)
    {
      member = ms->channel->clients->next;
      while (member)
	{
	  if (member->client != client)
	    client_write_buffer(member->client, RPL_NICK_B, old_name, client->nick);
	  member = member->next;
	}
      ms = ms->next;
    }
}
