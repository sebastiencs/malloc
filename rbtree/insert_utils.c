/*
** insert_utils.c for epitech in /home/chapui_s/travaux/malloc_ok/rbtree/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb 15 20:56:17 2015 chapui_s
** Last update Sun Feb 15 20:56:47 2015 chapui_s
*/

#include "rbtree.h"

t_rbnode g_rbnode_basis = {
  0,
  YFREE,
  (t_metadata*)0,
  (t_metadata*)0,
  0,
  (t_value**)0,
  SIZE_TAB_VALUES,
  1,
  RED,
  (t_rbnode*)0,
  (t_rbnode*)0
};

static void		*alloc_tab(size_t size)
{
  void			*new;
  size_t		true_size;

  true_size = ALIGN_BYTES(META_SIZE + (sizeof(new) * size));
  new = get_heap(true_size);
  if (new)
    bzero(GET_PAYLOAD(new), true_size - META_SIZE);
  return (new);
}

t_rbnode		*new_rbtree(t_metadata *node)
{
  t_rbnode		*new;

  if ((new = get_heap(ALIGN_BYTES(sizeof(*new)))) == (t_rbnode*)0)
    return ((t_rbnode*)0);
  memcpy(&(new->size_tab) , &(g_rbnode_basis.size_tab), sizeof(size_t) * 5);
  new->key = node->size;
  if ((new->tab_values = GET_PAYLOAD(alloc_tab(SIZE_TAB_VALUES)))
      == (void*)META_SIZE)
    return ((t_rbnode*)0);
  new->tab_values[0] = node;
  return (new);
}

int			resize_tab_values(t_metadata **old, t_rbnode *node)
{
  t_metadata		**new;
  size_t		size;

  size = (node->size_tab) << 1;
  if ((new = GET_PAYLOAD(alloc_tab(size))) == (void*)META_SIZE)
    return (-1);
  memcpy(new, old, (size >> 1) * sizeof(*new));
  ((t_metadata*)GET_NODE(node->tab_values))->free = YFREE;
  node->tab_values = new;
  node->size_tab = size;
  return (0);
}
