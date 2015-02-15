/*
** rbtree.c for epitech in /home/chapui_s/travaux/malloc/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Feb  2 15:48:40 2015 chapui_s
** Last update Sun Feb 15 23:13:46 2015 chapui_s
*/

#include "rbtree.h"

static int		insert_node(t_rbnode *node, t_metadata *new)
{
  t_metadata		**tmp;
  size_t		i;
  size_t		size;

  i = 0;
  tmp = node->tab_values;
  size = node->size_tab;
  if (node->nb_activ == size)
  {
    i = node->nb_activ;
    if ((resize_tab_values(tmp, node)) == -1)
      return (0);
  }
  else
  {
    while (i < size && tmp[i])
      i += 1;
  }
  node->nb_activ += 1;
  node->tab_values[i] = new;
  return (1);
}

static t_rbnode		*insert_this(t_rbnode *node, t_metadata *new)
{
  int			res;

  if (!node)
    return (new_rbtree(new));
  res = MY_COMPARE(new->size, node->key);
  if (res == 0)
  {
    if (insert_node(node, new) == 0)
      return ((t_rbnode*)0);
  }
  else if (res < 0)
    node->left = insert_this(node->left, new);
  else
    node->right = insert_this(node->right, new);
  if (IS_RED(node->right) && !IS_RED(node->left))
    node = rotate_left(node);
  if (IS_RED(node->left) && IS_RED(node->left->left))
    node = rotate_right(node);
  if (IS_RED(node->left) && IS_RED(node->right))
    flip_color(node);
  return (node);
}

t_rbnode		*insert_in_freed_list(t_rbnode *node, t_metadata *new)
{
  node = insert_this(node, new);
  if (node)
    node->color = BLACK;
  new->free = YFREE;
  return (node);
}
