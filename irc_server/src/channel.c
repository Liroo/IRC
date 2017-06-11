/*
** channel.c for channel in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 07:32:23 2017 Pierre Monge
** Last update Sun Jun 11 11:01:14 2017 Pierre Monge
*/

#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <string.h>

#include "struct.h"
#include "channel.h"

t_channel	*channel_create(char *name)
{
  t_channel	*new_channel;

  if (!(new_channel = malloc(sizeof(t_channel))))
    return (NULL);
  if (!(new_channel->name = strdup(name)))
    return (NULL);
  if (!(new_channel->clients = malloc(sizeof(t_member))))
    return (NULL);
  bzero(new_channel->clients, sizeof(t_member));
  new_channel->created_at = time(NULL);
  hash_table_insert(&server.channels, name, &new_channel->list);
  return (new_channel);
}

int		channel_user_exist(t_channel *channel, t_client *client)
{
  t_member	*member;

  member = channel->clients;
  while (member)
    {
      if (member->client && strcmp(client->nick, member->client->nick) == 0)
	return (1);
      member = member->next;
    }
  return (0);
}

int	channel_insert_user(t_channel *channel, t_client *client)
{
  t_member	*member;
  t_membership	*membership;

  if (channel_user_exist(channel, client))
    return (1);
  if (!(member = malloc(sizeof(t_member)))
      || !(membership = malloc(sizeof(t_membership))))
    return (-1);
  member->next = channel->clients->next;
  member->client = client;
  channel->clients->next = member;
  membership->next = client->channels->next;
  membership->channel = channel;
  client->channels->next = membership;
  return (0);
}

static void	channel_user_delete_channel(t_channel *channel, t_client *client)
{
  t_membership	*membership;
  t_membership	*m_next;

  membership = client->channels;
  while (membership)
    {
      m_next = membership;
      membership = membership->next;
      if (membership &&
	  strcmp(channel->name, membership->channel->name) == 0)
	{
	  m_next->next = membership->next;
	  free(membership);
	  break;
	}
    }
}

void		channel_delete_user(t_channel *channel, t_client *client)
{
  t_member	*member;
  t_member	*m_next;

  member = channel->clients;
  while (member)
    {
      m_next = member;
      member = member->next;
      if (member && strcmp(client->nick, member->client->nick) == 0)
	{
	  m_next->next = member->next;
	  free(member);
	  break;
	}
    }
  channel_user_delete_channel(channel, client);
  if (channel->clients->next == NULL)
    {
      list_del(channel->list.prev, channel->list.next);
      free(channel->clients);
      free(channel->name);
      free(channel);
    }
}
