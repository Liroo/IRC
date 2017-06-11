/*
** client_write.h for client_write in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 23:24:29 2017 Pierre Monge
** Last update Sat Jun 10 23:46:12 2017 Pierre Monge
*/

#ifndef CLIENT_WRITE_H
# define CLIENT_WRITE_H

# include <stdarg.h>

# include "struct.h"

/*
** client_write_buffer - write to the ring_buffer of client
** and set correct fd in fd_list_write
** client: client that is container of the fd and buffer
** format: format from vsnprintf
** ...: va_list used by format and vsnprint
*/
void	client_write_buffer(t_client *client, char *format, ...);

/*
** client_write_once - write the buffer to the fd (both contained by client)
** then remove the fd event listening if offset is 0 at the end
** client: client containing fd and buffer
*/
int	client_write_once(t_client *client);

#endif /* !CLIENT_WRITE_H */
