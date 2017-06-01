/*
** ring_buffer.h for ring_buffer in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun  1 18:01:45 2017 Pierre Monge
** Last update Thu Jun  1 18:16:03 2017 Pierre Monge
*/

#ifndef RING_BUFFER_H
# define RING_BUFFER_H

# define MAX_BUFFER_SIZE 4096

typedef struct	s_ring_buffer
{
  int		last_reached;
  char		buffer[MAX_BUFFER_SIZE + 1];
}		t_ring_buffer;

#endif /* !RING_BUFFER_H */
