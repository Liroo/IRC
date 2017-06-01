/*
** ring_buffer.c for ring_buffer in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Thu Jun  1 18:02:39 2017 Pierre Monge
** Last update Thu Jun  1 19:22:13 2017 Pierre Monge
*/

#include "ring_buffer.h"

/*
** What we are going to do is parse all commands in read buffer
** then store the last one if she's not finished
** -- Pierre
*/
