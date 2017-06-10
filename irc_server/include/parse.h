/*
** parse.h for parse in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 01:23:48 2017 Pierre Monge
** Last update Sat Jun 10 04:59:06 2017 Pierre Monge
*/

#ifndef PARSE_H
# define PARSE_H

# include "struct.h"

typedef struct	s_token
{
  char		*token;
  int		is_over;
}		t_token;

/*
** parse_buffer_to_token - parse buffer provided by client
**   and execute commands in
** client: client containing buffer
*/
int	parse_buffer_to_token(t_client *client);

#endif /* !PARSE_H */
