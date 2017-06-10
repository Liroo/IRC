/*
** parse.c for parse in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 01:29:14 2017 Pierre Monge
** Last update Sat Jun 10 06:43:19 2017 Pierre Monge
*/

#include <string.h>
#include <stdio.h>

#include "parse.h"
#include "struct.h"
#include "command.h"

static int	parse_token_get_first_word(char *token, char *command_title)
{
  int		i;
  char		*token_base;

  token_base = token;
  while (*token && *token == ' ')
    token++;
  if (!*token)
    return (0);
  i = 0;
  while (*token && *token != ' ' && i < MAX_COMMAND_SIZE)
    {
      command_title[i] = *token;
      token++;
      i++;
    }
  command_title[i] = 0;
  return (token - token_base);
}

static int		parse_token_to_command(char *token, t_client *client)
{
  int			len;
  t_client_command	command;

  len = strlen(token);
  bzero(&command, sizeof(t_command));
  if (token[len - 1] == '\r')
    token[len - 1] = '\0';
  command.title_end = parse_token_get_first_word(token, command.title);
  command.args = token;
  return (command_exec(client, command));
}

static t_token	parse_buffer_get_token(char *buffer, char *buffer_token)
{
  t_token	token;

  bzero(&token, sizeof(t_token));
  if (memchr(buffer, '\n', MAX_BUFFER_SIZE))
    token.is_over = 1;
  token.token = strtok(buffer_token, "\n");
  return (token);
}

int		parse_buffer_to_token(t_client *client)
{
  char		*buffer;
  t_token	token;
  int		len_not_over;
  int		ret_exec;

  buffer = client->read_buffer.buffer;
  token = parse_buffer_get_token(buffer, buffer);
  while (1)
    {
      if (!token.token)
	break;
      if (!token.is_over)
	{
	  len_not_over = strlen(token.token);
	  memmove(client->read_buffer.buffer, token.token, len_not_over);
	  client->read_buffer.offset = len_not_over;
	}
      else if ((ret_exec = parse_token_to_command(token.token, client)) != 0)
	return (ret_exec);
      token = parse_buffer_get_token(buffer, NULL);
    }
  return (0);
}
