/*
** command.c for command in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 03:07:33 2017 Pierre Monge
** Last update Sun Jun 11 13:50:20 2017 Pierre Monge
*/

#include <strings.h>

#include "command.h"
#include "client_write.h"

static t_command	*get_command_list()
{
  static t_command	command_entry[COMMAND_LIST_SIZE] = {
    { "nick", &command_nick },
    { "quit", &command_quit },
    { "ping", &command_ping },
    { "user", &command_user },
    { "users", &command_users },
    { "privmsg", &command_privmsg },
    { "join", &command_join },
    { "list", &command_list },
    { "part", &command_part },
    { "names", &command_names }
  };

  return (command_entry);
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
  client_write_buffer(client, ERR_421, command.args[0]);
  return (0);
}
