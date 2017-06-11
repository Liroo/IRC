/*
** c_user.c for user in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 00:40:31 2017 Pierre Monge
** Last update Sun Jun 11 03:22:24 2017 Pierre Monge
*/

#include "command.h"
#include "client_write.h"

int	command_user(t_client *client, t_client_command command)
{
  (void)command;
  return (client_write_buffer(client, RPL_001,
			      client->nick ? client->nick : ""), 0);
}
