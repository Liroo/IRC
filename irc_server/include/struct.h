/*
** struct.h for struct in /Users/pierre/Epitech/PSU/IRC
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun May 28 18:00:10 2017 Pierre Monge
** Last update Thu Jun  1 11:21:41 2017 Pierre Monge
*/

#ifndef STRUCT_H
# define STRUCT_H

# include "socket.h"

# define HOSTLEN 64
# define SERVICELEN 20

typedef struct s_client t_client;

# include "list.h"
# include "fd_list.h"

/*
** Be careful about the nomation
** A server is logicaly a client
** Note: a USER is not a server
** They use the same struct because
** server could connect to another server
** (not implemented (yet ? (Nahhh kiding, never)))
*/
struct		s_client
{
  time_t	created_at;
  t_list_head	list;
  t_socket_info	sock;
};

/*
** This is memory of the clients and chanels
**
** Edit: We'll stock fd_set here to manage less global -- Pierre
** Edit: Signal tester will be here (is this struct a trash memory ?) -- Pierre
*/
typedef struct	s_irc_server
{
  t_list_head	connection_queue;
  t_client	me;
  char		sig_handled;
  t_fdset	secure_fdset;
}		t_irc_server;

extern t_irc_server	server;

#endif /* !STRUCT_H */
