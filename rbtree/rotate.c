/*
** rotate.c for epitech in /home/chapui_s/travaux/malloc_ok/rbtree/rotate.c
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb 15 20:45:53 2015 chapui_s
** Last update Sun Feb 15 20:45:55 2015 chapui_s
*/

#include "rbtree.h"

t_rbnode		*rotate_left(t_rbnode *left)
{
  t_rbnode		*right;

  if (!left)
    return ((t_rbnode*)0);
  right = left->right;
  left->right = right->left;
  right->left = left;
  right->color = left->color;
  left->color = RED;
  return (right);
}

t_rbnode		*rotate_right(t_rbnode *right)
{
  t_rbnode		*left;

  if(!right)
    return ((t_rbnode*)0);
  left = right->left;
  right->left = left->right;
  left->right = right;
  left->color = right->color;
  right->color = RED;
  return (left);
}
