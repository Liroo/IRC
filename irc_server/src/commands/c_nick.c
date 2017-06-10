/*
** c_nick.c for c_nick in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 04:59:42 2017 Pierre Monge
** Last update Sat Jun 10 05:37:45 2017 Pierre Monge
*/

#include <stdio.h>

#include "command.h"

int	command_nick(t_client *client, t_client_command command)
{
  printf("nick\n");
  (void)client;
  (void)command;
  return (0);
}
