/*
** client_write.c for client_write in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun  1 11:51:58 2017 Pierre Monge
** Last update Sun Jun 11 20:32:34 2017 Pierre Monge
*/

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "client_write.h"
#include "fd_list.h"

/*
** Note: maximum write to fd is 4096
** This is actually a thing to fix but it will be not
** in epitech project -- Pierre
*/
void		client_write_buffer(t_client *client, char *format, ...)
{
  va_list	args;

  va_start(args, format);
  client->write_buffer.offset +=
    vsnprintf(&client->write_buffer.buffer[client->write_buffer.offset],
	      MAX_BUFFER_SIZE - client->write_buffer.offset,
	      format, args);
  va_end(args);
  if (client->write_buffer.offset > 0)
    FD_SET(client->fd, &server.secure_fdset.write_fds);
}

int	client_write_once(t_client *client)
{
  int	write_ret;

  write_ret = write(client->fd,
		    client->write_buffer.buffer,
		    client->write_buffer.offset);
  if (write_ret == -1)
    return (-1);
  client->write_buffer.offset -= write_ret;
  if (client->write_buffer.offset == 0)
    {
      client->write_buffer.buffer[0] = 0;
      FD_CLR(client->fd, &server.secure_fdset.write_fds);
    }
  else
    {
      memmove(client->write_buffer.buffer,
	      &client->write_buffer.buffer[write_ret],
	      client->write_buffer.offset);
      client->write_buffer.buffer[client->write_buffer.offset] = 0;
    }
  return (0);
}
