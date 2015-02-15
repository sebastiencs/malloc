/*
** rbtree.c for epitech in /home/chapui_s/travaux/my_malloc2/rbtree.c
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Feb  2 15:48:40 2015 chapui_s
** Last update Sun Feb 15 21:19:24 2015 chapui_s
*/

#include "rbtree.h"

t_rbnode		*get_key(t_rbnode *node, t_key key)
{
  int			cmp;

  while (node)
  {
    if (!(cmp = MY_COMPARE(key, node->key)))
      return (node);
    node = ((cmp < 0) ? (node->left) : (node->right));
  }
  return ((t_rbnode*)0);
}

t_rbnode		*min(t_rbnode *node)
{
  if (!node)
    return ((t_rbnode*)0);
  while (node->left)
    node = node->left;
  return (node);
}

t_rbnode	*balance_me_that(t_rbnode *node)
{
  if (IS_RED(node->right))
    node = rotate_left(node);
  if (IS_RED(node->left) && IS_RED(node->left->left))
    node = rotate_right(node);
  if (IS_RED(node->left) && IS_RED(node->right))
    flip_color(node);
  return (node);
}

t_rbnode		*move_red_to_left(t_rbnode *node)
{
  flip_color(node);
  if (node && node->right && IS_RED(node->right->left))
  {
    node->right = rotate_right(node->right);
    node = rotate_left(node);
    flip_color(node);
  }
  return (node);
}

t_rbnode		*move_red_to_right(t_rbnode *node)
{
  flip_color(node);
  if (node && node->left && IS_RED(node->left->left))
  {
    node = rotate_right(node);
    flip_color(node);
  }
  return (node);
}
