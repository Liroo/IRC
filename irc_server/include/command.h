/*
** command.h for command in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 02:52:00 2017 Pierre Monge
** Last update Sat Jun 10 05:36:33 2017 Pierre Monge
*/

#ifndef COMMAND_H
# define COMMAND_H

# define MAX_COMMAND_SIZE 32
# define COMMAND_LIST_SIZE 2

# include "struct.h"

typedef struct	s_client_command
{
  char		title[MAX_COMMAND_SIZE + 1];
  int		title_end;
  char		*args;
}		t_client_command;

typedef int	(*t_command_func)(t_client *client, t_client_command command);
typedef struct		s_command
{
  char			*title;
  t_command_func	exec;
}			t_command;

/*
** command_exec - execute a command after the parser
** client: client running the command
** command: command provided by user
*/
int	command_exec(t_client *client, t_client_command command);

/*
** Command list pointer
** from command repository
*/
int	command_nick(t_client *client, t_client_command command);
int	command_quit(t_client *client, t_client_command command);

#endif /* !COMMAND_H */
