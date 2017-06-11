/*
** broadcast.h for broadcast in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 09:00:17 2017 Pierre Monge
** Last update Sun Jun 11 13:52:09 2017 Pierre Monge
*/

#ifndef BROADCAST_H
# define BROADCAST_H

# include "struct.h"

/*
** broadcast_message_channel - broadcast a message to a channel
** client: client sending the message
** channel: channel to send to message
** message: message to send
*/
void	broadcast_message_channel(t_client *client, t_channel *channel,
				  char *message);

/*
** broadcast_join_channel - broadcast to all member the joining of a new member
** client: client who has joined
** channel: channel joined
*/
void	broadcast_join_channel(t_client *client, t_channel *channel);

/*
** broadcast_part_channel - broadcast to all member the quit of a member
** client: client who has quit
** channel: channel quit
*/
void	broadcast_part_channel(t_client *client, t_channel *channel);

/*
** broadcast_rename_client - broadcast to all channels the new nick of a member
** client: client who has changed nick
** old_name: old_name to comunicate
*/
void	broadcast_rename_client(t_client *client, char *old_name);

#endif /* !BROADCAST_H */
