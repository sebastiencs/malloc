/*
** free.c for epitech in /home/chapui_s/travaux/malloc/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb 15 19:50:03 2015 chapui_s
** Last update Sun Feb 15 23:03:29 2015 chapui_s
*/

#include "malloc.h"

extern t_malloc	g_info;

static void	invalid_pointer(void *ptr)
{
  printf("Error in '%s': free(): invalid pointer: %p\n",
	 ((__progname) ? (__progname) : ("Unknow")), ptr);
  abort();
}

static void	double_free(void *ptr)
{
  printf("Error in '%s': free(): double free: %p\n",
	 ((__progname) ? (__progname) : ("Unknow")), ptr);
  abort();
}

static inline t_metadata	*try_fusion(t_metadata *node)
{
  while (IS_FREE(node->prev))
  {
    g_info.root_rbtree = remove_from_freed_list(g_info.root_rbtree,
						node->prev);
    node = fusion(node->prev, node);
  }
  while (IS_FREE(node->next))
  {
    g_info.root_rbtree = remove_from_freed_list(g_info.root_rbtree,
						node->next);
    node = fusion(node, node->next);
  }
  return (node);
}

static inline void	change_break(t_metadata *node)
{
  size_t		pages_to_remove;

  if (node->prev)
  {
    node->prev->next = (t_metadata*)0;
    g_info.last_node = node->prev;
    g_info.end_in_page = (void*)g_info.last_node + g_info.last_node->size;
  }
  else
  {
    g_info.end_in_page = g_info.last_node;
    g_info.last_node = (t_metadata*)0;
  }
  g_info.page_remaining += node->size;
  pages_to_remove = g_info.page_remaining / g_info.page_size;
  brk((sbrk(0) - (pages_to_remove * g_info.page_size)));
  g_info.page_remaining = g_info.page_remaining
    - (pages_to_remove * g_info.page_size);
}

void		free(void *ptr)
{
  t_metadata	*node;

  if (!ptr)
    return ;
  pthread_mutex_lock(&(g_info.mutex));
  node = GET_NODE(ptr);
  if (ptr < g_info.first_block || ptr > g_info.end_in_page || !IS_VALID(node))
    invalid_pointer(ptr);
  if (node->free == YFREE)
    double_free(ptr);
  node = try_fusion(node);
  if (!node->next)
    change_break(node);
  else
    g_info.root_rbtree = insert_in_freed_list(g_info.root_rbtree, node);
  pthread_mutex_unlock(&(g_info.mutex));
}
