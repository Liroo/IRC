/*
** fd_list.h for FD_LIST in /Users/pierre/Epitech/PSU/IRC
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Mon May 29 15:20:26 2017 Pierre Monge
** Last update Mon May 29 23:42:34 2017 Pierre Monge
*/

#ifndef FD_LIST
# define FD_LIST

# define SELECT_DELAY_SEC 60

# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct	s_fdset
{
  fd_set	read_fds;
  fd_set	write_fds;
  int		num;
}		t_fdset;

/*
** These function interact with fd
** They add the fd to the fd_set list
** and one is doing the job of accept function
*/
int	fd_add(int fd);
int	fd_remove(int fd);
t_fdset	fd_select(time_t delay);
int	fd_accept(int sock_fd);

#endif /* !FD_LIST */
