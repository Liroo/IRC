/*
** socket.h for socket in /Users/pierre/Epitech/PSU/IRC
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sun May 28 16:15:41 2017 Pierre Monge
** Last update Mon May 29 14:20:47 2017 Pierre Monge
*/

#ifndef SOCKET_H
# define SOCKET_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>

/*
** t_socket_info: structure to describe the socket information
**   such as fd, addr, etc..
**
** int fd: file descriptor of the socket
** struct sockaddr_in addr: information about socket address and binding
** socklen_t addr_len: len in memory of (addr)
*/
typedef struct		s_socket_info {
  unsigned char		is_open;
  int			fd;
  struct sockaddr_in	addr;
  socklen_t		addr_len;
}			t_socket_info;

/*
**  Prototype are defined in /etc/protocols
**  The one who are using provide TCP implementation
**
**  As long as TCP existed, I assume there is not
**  possible that some distribution didn't implement
**  TCP protocol
*/
# define PROTOTYPE_NAME "TCP"

/*
**  Max connections handle by server
*/
# define MAX_CONNECTIONS 10240

int	socket_open(t_socket_info *socket_info, unsigned int port);
char	*socket_get_ip(t_socket_info socket_info);
int	socket_close(int fd);
void	socket_loop();

#endif /* !SOCKET_H */
