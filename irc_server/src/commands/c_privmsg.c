/*
** c_privmsg.c for privmsg in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun Jun 11 05:10:24 2017 Pierre Monge
** Last update Sun Jun 11 06:41:18 2017 Pierre Monge
*/

#include "command.h"
#include "client_write.h"

int		command_privmsg(t_client *client, t_client_command command)
{
  t_client	*client_remote;

  if (!client->nick)
    return (client_write_buffer(client, ERR_451), 0);
  if (command.argc < 2)
    return (client_write_buffer(client, ERR_411, "PRIVMSG"), 0);
  if (command.argc < 3)
    return (client_write_buffer(client, ERR_412), 0);
  if (!(client_remote =
	hash_table_find_client(&server.clients, command.args[1])))
    return (client_write_buffer(client, ERR_401, command.args[1]), 0);
  return (client_write_buffer(client_remote, RPL_PRIVMSG,
			      client->nick, command.args[2]), 0);
}
