/*
** c_ping.c for c_ping in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 20:44:06 2017 Pierre Monge
** Last update Sun Jun 11 00:55:28 2017 Pierre Monge
*/

#include <stdio.h>

#include "command.h"
#include "client_write.h"

int	command_ping(t_client *client, t_client_command command)
{
  (void)command;
  return (client_write_buffer(client, RPL_PING), 0);
}
