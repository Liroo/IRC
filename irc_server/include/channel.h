/*
** channel.h for channel in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 07:33:17 2017 Pierre Monge
** Last update Sun Jun 11 08:42:52 2017 Pierre Monge
*/

#ifndef CHANNEL_H
# define CHANNEL_H

# include "struct.h"

/*
** channel_create - create a channel
** name: name of the new channel
*/
t_channel	*channel_create(char *name);

/*
** channel_insert_user - insert channel in user and user in channel
** channel: channel focused
** client: client focused
**
** Note: DOES NOT PROPAGATE ANY MESSAGE -- Pierre
*/
int	channel_insert_user(t_channel *channel, t_client *client);

/*
** channel_delete_user - delete channel in user and user in channel
** channel: channel focused
** client: client focused
**
** Note: DOES NOT PROPAGATE ANY MESSAGE -- Pierre
*/
void	channel_delete_user(t_channel *channel, t_client *client);

#endif /* !CHANNEL_H */
