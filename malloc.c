/*
** malloc.c for epitech in /home/chapui_s/travaux/malloc/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Feb  2 15:52:40 2015 chapui_s
** Last update Sun Feb 15 23:30:22 2015 chapui_s
*/

#include "malloc.h"

t_malloc g_info = {
  .root_rbtree = (t_rbnode*)0,
  .last_node = (t_metadata*)0,
  .end_in_page = (void*)0,
  .first_block = (void*)0,
  .page_size = 0,
  .mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER,
  .page_remaining = 0
};

#ifdef FIND_BEST

static inline t_rbnode	*find_best(t_rbnode *node, size_t size)
{
  t_rbnode		*tmp;

  tmp = (t_rbnode*)0;
  while (node)
  {
    if (node->key >= size)
    {
      tmp = node;
      node = node->left;
    }
    else
      node = node->right;
  }
  return (tmp);
}

static t_metadata	*search_freed_block(t_rbnode *node, size_t size)
{
  t_metadata		**tab;
  size_t		size_tab;
  size_t		i;
  t_rbnode		*tmp;

  i = 0;
  tmp = find_best(node, size);
  if (tmp)
  {
    size_tab = tmp->size_tab;
    tab = tmp->tab_values;
    while (i < size_tab)
    {
      if (tab[i])
	return (tab[i]);
      i += 1;
    }
  }
  return ((t_metadata*)0);
}

#else /* !FIND_BEST */

static t_metadata	*search_freed_block(t_rbnode *node, size_t size)
{
  t_metadata		**tab;
  size_t		size_tab;
  size_t		i;

  i = 0;
  while (node)
  {
    if (node->key >= size)
    {
      size_tab = node->size_tab;
      tab = node->tab_values;
      while (i < size_tab)
      {
	if (tab[i])
	  return (tab[i]);
	i += 1;
      }
    }
    node = node->right;
  }
  return ((t_metadata*)0);
}

#endif /* !FIND_BEST */

static void	*split_block(t_metadata *node, size_t size)
{
  t_metadata	*new;

  g_info.root_rbtree = remove_from_freed_list(g_info.root_rbtree, node);
  if (node->size > size + sizeof(size_t)
      && node->size - size > sizeof(t_rbnode) + SIZE_DEFAULT_BLOCK)
  {
    new = (void*)node + size;
    new->size = node->size - size;
    new->free = YFREE;
    new->prev = node;
    new->next = node->next;
    node->next = new;
    node->size = size;
    if (new->next)
      new->next->prev = new;
    g_info.root_rbtree = insert_in_freed_list(g_info.root_rbtree, new);
  }
  return (node);
}

void		*malloc(size_t size)
{
  t_metadata	*tmp;
  void		*ptr;

  pthread_mutex_lock(&(g_info.mutex));
  if (size < SIZE_DEFAULT_BLOCK)
    size = SIZE_DEFAULT_BLOCK;
  size = ALIGN_BYTES(size) + META_SIZE;
  if (!g_info.page_size)
    g_info.page_size = getpagesize();
  if ((tmp = search_freed_block(g_info.root_rbtree, size)))
    ptr = split_block(tmp, size);
  else
    ptr = get_heap(size);
  pthread_mutex_unlock(&(g_info.mutex));
  return ((ptr) ? (GET_PAYLOAD(ptr)) : (0));
}
