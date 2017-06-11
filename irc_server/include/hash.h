/*
** hash.h for hash in /Users/pierre/Epitech/PSU/IRC/irc_server
**
** Made by Pierre Monge
** Login   <pierre@epitech.net>
**
** Started on  Sat Jun 10 07:07:20 2017 Pierre Monge
** Last update Sat Jun 10 23:47:32 2017 Pierre Monge
*/

#ifndef HASH_H
# define HASH_H

# include "list.h"

typedef struct	s_hash_entry
{
  t_list_head	list;
}		t_hash_entry;

# define HASH_TABLE_SIZE 126

typedef struct	s_hash_table
{
  t_hash_entry	table[HASH_TABLE_SIZE];
}		t_hash_table;

# include "struct.h"

/*
** hash_table_init - init new hash table
** hash_table: hash table to init
*/
void		hash_table_init(t_hash_table *hash_table);

/*
** hash_table_insert - insert a new entry in hash table
** hash_table: hash table used
** key: key used to know the index after hashing it
** list: entry to add
*/

void		hash_table_insert(t_hash_table *hash_table,
				  char *key,
				  t_list_head *entry);

/*
** hash_table_find_client - find client in appropriate hash table
** hash_table: hash table used to find
** key: key to find compared to nick of client
*/

t_client	*hash_table_find_client(t_hash_table *hash_table,
					char *key);


#endif /* !HASH_H */
