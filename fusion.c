/*
** fusion.c for epitech in /home/chapui_s/travaux/malloc/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb 15 19:49:50 2015 chapui_s
** Last update Sun Feb 15 23:03:21 2015 chapui_s
*/

#include "malloc.h"

extern t_malloc	g_info;

t_metadata	*fusion(t_metadata *first, t_metadata *second)
{
  first->size += second->size;
  first->next = second->next;
  if (first->next)
    first->next->prev = first;
  else
    g_info.last_node = first;
  return (first);
}
