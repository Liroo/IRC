/*
** sig.c for sig in /Users/pierre/Epitech/PSU/IRC
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Mon May 29 22:57:48 2017 Pierre Monge
** Last update Fri Jun  9 18:48:29 2017 Pierre Monge
*/

#include <stdio.h>
#include <signal.h>

#include "struct.h"
#include "sig.h"

void	sig_handler(int sig __attribute__((__unused__)))
{
  server.sig_handled = 1;
}

int			sig_set()
{
  sigset_t		blockset;
  struct sigaction	sa;

  sigemptyset(&blockset);
  sigaddset(&blockset, SIGINT);
  sigprocmask(SIG_BLOCK, &blockset, NULL);
  sa.sa_handler = sig_handler;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  if (sigaction(SIGINT, &sa, NULL) == -1)
    return (perror("sigaction"), -1);
  return (0);
}
