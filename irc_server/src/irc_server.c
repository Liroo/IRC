/*
** main.c<irc_server> for main_server in /Users/pierre/Epitech/PSU/IRC
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat May 27 06:33:50 2017 Pierre Monge
** Last update Tue May 30 06:26:40 2017 Pierre Monge
*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "struct.h"
#include "socket.h"
#include "fd_list.h"
#include "sig.h"

t_irc_server	server;

int		main(int argc, char *argv[])
{
  if (argc != 2)
    return (fprintf(stderr, "Usage: %s port\n", argv[0]), 0);
  bzero(&server, sizeof(t_irc_server));
  server.highest_fd = -1;
  if (socket_open(&server.me.sock, atoi(argv[1])) == -1)
    return (84);
  FD_ZERO(&server.secure_fdset.read_fds);
  FD_SET(server.me.sock.fd, &server.secure_fdset.read_fds);
  server.highest_fd = server.me.sock.fd;
  sig_set();
  if (socket_loop() == -1)
    return (socket_close(server.me.sock.fd), 84);
  if (socket_close(server.me.sock.fd) == -1)
    return (84);
  return (0);
}
