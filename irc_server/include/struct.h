/*
** struct.h for struct in /Users/pierre/Epitech/PSU/IRC
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun May 28 18:00:10 2017 Pierre Monge
** Last update Mon May 29 23:38:45 2017 Pierre Monge
*/

#ifndef STRUCT_H
# define STRUCT_H

# include "fd_list.h"
# include "socket.h"

/*
** Be careful about the nomation
** A server is logicaly a client
** Note: a USER is not a server
** They use the same struct because
** server could connect to another server (not implemented)
*/
typedef struct	s_client
{
  t_socket_info	sock;
}		t_client;

/*
** This is memory of the clients
** and some chanels
** (me) is the server client itself
** (clients) are the clients ordered by fd
*/
typedef struct	s_irc_server
{
  t_client	me;
  t_client	clients[MAX_CONNECTIONS + 1];
  char		sig_handled;
  int		highest_fd;
  t_fdset	secure_fdset;
}		t_irc_server;

/*
** Global is defined for some reason:
**
** I had two choices, one where I had to create reference
** of my struct server. The other was simply to pass the struct
** w/o ref directly by the stack
**
** The two choices not enought optimized... One was passing by reference
** create too much asm instructions (rdi) which is long.
** The other was to pass by the stack but copying the same sruct
** on top of the stack was memory horrible...
**
** The only way to optimize both things is to create an extern global
*/
extern t_irc_server	server;

#endif /* !STRUCT_H */
