/*
** command.h for command in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 02:52:00 2017 Pierre Monge
** Last update Sun Jun 11 04:03:25 2017 Pierre Monge
*/

#ifndef COMMAND_H
# define COMMAND_H

# define MAX_COMMAND_SIZE 32
# define COMMAND_LIST_SIZE 5

/*
** based on RFC maximum of arguments in a message is:
**   prefix       1
**   command    + 1
**   parameters + 15
**              = 17
**
** Note: On this server, we are not gonna handle prefix, anyway keeping
** 8octets more in memory is not so badly and could be useful -- Pierre
*/
# define MAX_COMMAND_ARGS_SIZE 17

# include "struct.h"

typedef struct	s_client_command
{
  char		title[MAX_COMMAND_SIZE + 1];
  int		title_end;
  char		*args[MAX_COMMAND_ARGS_SIZE + 1];
}		t_client_command;

typedef int	(*t_command_func)(t_client *client, t_client_command command);
typedef struct		s_command
{
  char			*title;
  t_command_func	exec;
}			t_command;

# define CR_LF "\r\n"
# define SRV_PRE ":insert.ip.here"

/*
** command_exec - execute a command after the parser
** client: client running the command
** command: command provided by user
*/
int	command_exec(t_client *client, t_client_command command);


# define RPL_001				  \
  SRV_PRE " "					  \
  "001 %s :Welcome to the Internet Relay Network" \
  "" CR_LF
# define RPL_392				\
  SRV_PRE " "					\
  "392 :UserID"					\
  "" CR_LF
# define RPL_393				\
  SRV_PRE " "					\
  "393 :%-8s"					\
  "" CR_LF
# define RPL_394				\
  SRV_PRE " "					\
  "394 :End of users"				\
  "" CR_LF

# define ERR_431	   \
  SRV_PRE " "		   \
  "431 :No nickname given" \
  "" CR_LF
# define ERR_432				\
  SRV_PRE " "					\
 "432 %s :Erroneus nickname"			\
 "" CR_LF
# define ERR_433				\
  SRV_PRE " "					\
  "433 %s :Nickname is already in use"		\
  "" CR_LF
# define ERR_451				\
  SRV_PRE " "					\
  "451 :You have not registered"		\
  "" CR_LF

/*
** Command list
*/
# define RPL_NICK				\
  SRV_PRE " "					\
  "NICK :%s"					\
  "" CR_LF
# define RPL_PING				\
  SRV_PRE " "					\
  "PONG"					\
  " " SRV_PRE					\
  " " SRV_PRE					\
  "" CR_LF

int	command_nick(t_client *client, t_client_command command);
int	command_quit(t_client *client, t_client_command command);
int	command_ping(t_client *client, t_client_command command);
int	command_user(t_client *client, t_client_command command);
int	command_users(t_client *client, t_client_command command);

#endif /* !COMMAND_H */
