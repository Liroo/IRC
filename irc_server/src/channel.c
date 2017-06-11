/*
** channel.c for channel in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 07:32:23 2017 Pierre Monge
** Last update Sun Jun 11 07:44:34 2017 Pierre Monge
*/

#include <stdlib.h>
#include <strings.h>
#include <time.h>

#include "struct.h"
#include "channel.h"

t_channel	*channel_create(char *name)
{
  t_channel	*new_channel;

  if (!(new_channel = malloc(sizeof(t_channel))))
    return (NULL);
  if (!(new_channel->name = strdup(name)))
    return (NULL);
  if (!(new_channel->members = malloc(sizeof(t_member))))
    return (NULL);
  bzero(new_channel->members, sizeof(t_member));
  new_channel->created_at = time(NULL);
  hash_table_insert(&server.channels, name, &new_channel->list);
  return (new_channel);
}

t_channel	*channel_insert_user(t_channel *channel, t_client *client)
{
  (void)channel;
  (void)client;
  return (NULL);
}

t_channel	*channel_delete_user(t_channel *channel, t_client *client)
{
  (void)channel;
  (void)client;
  return (NULL);
}
