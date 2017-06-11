/*
** struct.h for struct in /Users/pierre/Epitech/PSU/IRC
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun May 28 18:00:10 2017 Pierre Monge
** Last update Sun Jun 11 07:46:42 2017 Pierre Monge
*/

#ifndef STRUCT_H
# define STRUCT_H

# include "socket.h"

# define HOSTLEN 64
# define SERVICELEN 20

typedef struct s_client		t_client;
typedef struct s_channel	t_channel;

# include "list.h"
# include "fd_list.h"
# include "ring_buffer.h"

typedef struct		s_membership
{
  struct s_membership	*next;
  t_channel		*channel;
}			t_membership;

typedef struct		s_member
{
  struct s_member	*next;
  t_client		*client;
}			t_member;

/*
** Be careful about the nomation
** A server is logicaly a client
** Note: a USER is not a server
** They use the same struct because
** server could connect to another server
** (not implemented (yet ? (Nahhh kiding, never)))
**
**
** Note: get a nick significate client is authenticated -- Pierre
*/
struct		s_client
{
  int		fd;
  time_t	created_at;
  t_list_head	list;
  t_socket_info	sock;
  t_ring_buffer	read_buffer;
  t_ring_buffer	write_buffer;

  t_membership	*channels;
  char		*nick;
};

struct	s_channel
{
  time_t	created_at;
  t_list_head	list;

  t_member	*members;
  char		*name;
};

# include "hash.h"

/*
** This is memory of the clients and chanels
*/
typedef struct	s_irc_server
{
  t_list_head	connection_queue;
  t_hash_table	clients;
  t_hash_table	channels;
  t_client	me;
  char		sig_handled;
  t_fdset	secure_fdset;
}		t_irc_server;

extern t_irc_server	server;

#endif /* !STRUCT_H */
