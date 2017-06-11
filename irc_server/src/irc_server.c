/*
** main.c<irc_server> for main_server in /Users/pierre/Epitech/PSU/IRC
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat May 27 06:33:50 2017 Pierre Monge
** Last update Sun Jun 11 14:39:29 2017 Pierre Monge
*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

#include "struct.h"
#include "socket.h"
#include "fd_list.h"
#include "sig.h"
#include "list.h"
#include "hash.h"
#include "channel.h"

t_irc_server	server;

void	delete_client(t_client *client)
{
  t_membership	*channel;
  t_membership	*next;

  list_del(client->list.prev, &client->list);
  socket_close(client->fd);
  FD_CLR(client->fd, &server.secure_fdset.write_fds);
  fd_remove(client->fd);
  channel = client->channels;
  while (channel)
    {
      next = channel->next;
      if (channel->channel)
	channel_delete_user(channel->channel, client);
      channel = next;
    }
  free(client->channels);
  if (client->nick)
    free(client->nick);
  free(client);
}

void	free_registered_client()
{
  t_client	*client;
  t_list_head	*head;
  t_list_head	*pos;
  t_list_head	*next_safe;
  int		i;

  i = 0;
  while (i < HASH_TABLE_SIZE)
    {
      head = &server.clients.table[i].list;
      pos = list_get_first(head);
      while (pos != head)
	{
	  next_safe = pos->next;
	  client = list_entry(pos, t_client, list);
	  delete_client(client);
	  pos = next_safe;
	}
      i++;
    }
}

void	free_not_registered_client()
{
  t_client	*client;
  t_list_head	*head;
  t_list_head	*pos;
  t_list_head	*next_safe;

  head = &server.connection_queue;
  pos = list_get_first(head);
  while (pos != head)
    {
      next_safe = pos->next;
      client = list_entry(pos, t_client, list);
      delete_client(client);
      pos = next_safe;
    }
}

void		free_irc_server()
{
  free_not_registered_client();
  free_registered_client();
}

int		main(int argc, char *argv[])
{
  if (argc != 2)
    return (fprintf(stderr, "Usage: %s port\n", argv[0]), 0);
  bzero(&server, sizeof(t_irc_server));
  bzero(&fd_entry, sizeof(t_fd_entry));
  server.secure_fdset.highest_fd = -1;
  list_init(&server.connection_queue);
  hash_table_init(&server.clients);
  hash_table_init(&server.channels);
  if (socket_open(&server.me.sock, atoi(argv[1])) == -1)
    return (84);
  server.me.created_at = time(NULL);
  FD_ZERO(&server.secure_fdset.read_fds);
  FD_SET(server.me.sock.fd, &server.secure_fdset.read_fds);
  server.secure_fdset.highest_fd = server.me.sock.fd;
  sig_set();
  if (socket_loop() == -1)
    return (socket_close(server.me.sock.fd), 84);
  if (socket_close(server.me.sock.fd) == -1)
    return (84);
  free_irc_server();
  return (0);
}
