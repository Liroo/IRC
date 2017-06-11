/*
** ring_buffer.c for ring_buffer in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun  1 18:02:39 2017 Pierre Monge
** Last update Sun Jun 11 02:50:29 2017 Pierre Monge
*/

#include <unistd.h>
#include <stdio.h>

#include "ring_buffer.h"

/*
** What we are going to do is parse all commands in read buffer
** then store the last one if she's not finished
** -- Pierre
*/

int	ring_buffer_read(t_ring_buffer *ring_buffer, int fd)
{
  int	ret_read;

  ret_read = read(fd, &(ring_buffer->buffer[ring_buffer->offset]),
		  MAX_BUFFER_SIZE - ring_buffer->offset);
  if (ret_read < 0)
    return (perror("read"), -1);
  ring_buffer->buffer[ring_buffer->offset + ret_read] = 0;
  return (ret_read);
}
