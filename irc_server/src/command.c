/*
** command.c for command in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 03:07:33 2017 Pierre Monge
** Last update Sun Jun 11 05:13:05 2017 Pierre Monge
*/

#include <strings.h>

#include "command.h"

static t_command	*get_command_list()
{
  static t_command	command_list[COMMAND_LIST_SIZE] = {
    { "nick", &command_nick },
    { "quit", &command_quit },
    { "ping", &command_ping },
    { "user", &command_user },
    { "users", &command_users },
    { "privmsg", &command_privmsg }
  };

  return (command_list);
}

int		command_exec(t_client *client, t_client_command command)
{
  t_command	*command_list;
  int		i;

  command_list = get_command_list();
  i = 0;
  while (i < COMMAND_LIST_SIZE)
    {
      if (strcasecmp(command_list[i].title, command.title) == 0)
	return (command_list[i].exec(client, command));
      i++;
    }
  // here we should handle message to channel
  return (0);
}
