/*
** flip_color.c for epitech in /home/chapui_s/travaux/malloc/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb 15 21:18:23 2015 chapui_s
** Last update Sun Feb 15 23:13:11 2015 chapui_s
*/

#include "rbtree.h"

void		flip_color(t_rbnode *node)
{
  node->color = !(node->color);
  node->left->color = !(node->left->color);
  node->right->color = !(node->right->color);
}
