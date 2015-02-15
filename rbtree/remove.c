/*
** remove.c for epitech in /home/chapui_s/travaux/malloc_ok/rbtree/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb 15 21:04:49 2015 chapui_s
** Last update Sun Feb 15 23:17:01 2015 chapui_s
*/

#include "rbtree.h"

static t_rbnode		*remove_min(t_rbnode *node)
{
  if (!node)
    return ((t_rbnode*)0);
  if (!node->left)
  {
    node->free = YFREE;
    return ((t_rbnode*)0);
  }
  if (!IS_RED(node->left) && !IS_RED(node->left->left))
    node = move_red_to_left(node);
  node->left = remove_min(node->left);
  return (balance_me_that(node));
}

static t_rbnode		*remove_node(t_rbnode *node, t_key key, t_rbnode *tmp)
{
  if (IS_RED(node->left))
    node = rotate_right(node);
  if (!MY_COMPARE(key, node->key) && !node->right)
  {
    node->free = YFREE;
    return ((t_rbnode*)0);
  }
  if (node->right)
  {
    if (!IS_RED(node->right) && !IS_RED(node->right->left))
      node = move_red_to_right(node);
    if (!MY_COMPARE(key, node->key))
    {
      tmp = min(node->right);
      node->tab_values = tmp->tab_values;
      node->size_tab = tmp->size_tab;
      node->key = tmp->key;
      node->right = remove_min(node->right);
      node->nb_activ = tmp->nb_activ;
    }
    else
      node->right = remove_key(node->right, key);
  }
  return (node);
}

t_rbnode		*remove_key(t_rbnode *node, t_key key)
{
  t_rbnode		*tmp;

  if (!node)
    return ((t_rbnode*)0);
  if (MY_COMPARE(key, node->key) == -1)
  {
    if (node->left)
    {
      if (!IS_RED(node->left) && !IS_RED(node->left->left))
	node = move_red_to_left(node);
      node->left = remove_key(node->left, key);
    }
  }
  else
    if ((node = remove_node(node, key, tmp)) == (void*)0)
      return ((void*)0);
  return (balance_me_that(node));
}

static t_rbnode		*remove_k(t_rbnode *node, t_key key)
{
  node = remove_key(node, key);
  if (node)
    node->color = BLACK;
  return (node);
}

t_rbnode		*remove_from_freed_list(t_rbnode *node,
						t_metadata *meta)
{
  t_rbnode		*tmp;
  t_metadata		**tab;
  size_t		i;
  size_t		size;

  if ((tmp = get_key(node, meta->size)))
  {
    meta->free = NFREE;
    tab = tmp->tab_values;
    i = 0;
    size = tmp->size_tab;
    while (i < size)
    {
      if (tab[i] == meta)
      {
	tab[i] = (t_metadata*)0;
	tmp->nb_activ -= 1;
	if (tmp->nb_activ == 0)
	  return (remove_k(node, meta->size));
	return (node);
      }
      i += 1;
    }
  }
  return ((t_rbnode*)0);
}
