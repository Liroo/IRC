/*
** hash.c for hash in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 07:07:46 2017 Pierre Monge
** Last update Sun Jun 11 07:49:45 2017 Pierre Monge
*/

#include <string.h>

#include "hash.h"
#include "list.h"
#include "struct.h"

/*
** hash_index - really simple hash function
** key: key to hash to find correct index
*/
static int	hash_index(char *key)
{
  int		index;

  index = 0;
  while (*key)
    {
      index += *key;
      key++;
    }
  return (index % HASH_TABLE_SIZE);
}

void	hash_table_init(t_hash_table *hash_table)
{
  int	i;

  i = 0;
  while (i < HASH_TABLE_SIZE)
    {
      list_init(&hash_table->table[i].list);
      i++;
    }
}

void	hash_table_insert(t_hash_table *hash_table, char *key, t_list_head *entry)
{
  int	index;

  index = hash_index(key);
  list_add_tail(entry, &hash_table->table[index].list);
}

t_client	*hash_table_find_client(t_hash_table *hash_table, char *key)
{
  int		index;
  t_list_head	*list;
  t_list_head	*head;
  t_client	*client;

  index = hash_index(key);
  head = &hash_table->table[index].list;
  list = list_get_first(head);
  while (list != head)
    {
      client = list_entry(list, struct s_client, list);
      if (strcmp(key, client->nick) == 0)
	return (client);
      list = list->next;
    }
  return (NULL);
}

t_channel	*hash_table_find_server(t_hash_table *hash_table, char *key)
{
  int		index;
  t_list_head	*list;
  t_list_head	*head;
  t_channel	*channel;

  index = hash_index(key);
  head = &hash_table->table[index].list;
  list = list_get_first(head);
  while (list != head)
    {
      channel = list_entry(list, struct s_channel, list);
      if (strcmp(key, channel->name) == 0)
	return (channel);
      list = list->next;
    }
  return (NULL);
}
