/*
** ring_buffer.h for ring_buffer in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun  1 18:01:45 2017 Pierre Monge
** Last update Sat Jun 10 04:58:05 2017 Pierre Monge
*/

#ifndef RING_BUFFER_H
# define RING_BUFFER_H

# define MAX_BUFFER_SIZE 4096

typedef struct	s_ring_buffer
{
  char		buffer[MAX_BUFFER_SIZE + 1];
  int		offset;
}		t_ring_buffer;

/*
** ring_buffer_read - read a fd using offset
** ring_buffer: ring_buffer struct provided offset and actual buffer
** fd: fd to read
*/
int	ring_buffer_read(t_ring_buffer *ring_buffer, int fd);

#endif /* !RING_BUFFER_H */
