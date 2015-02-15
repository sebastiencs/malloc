/*
** get_heap.c for epitech in /home/chapui_s/travaux/malloc_ok/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb 15 19:52:25 2015 chapui_s
** Last update Sun Feb 15 22:06:22 2015 chapui_s
*/

#include "malloc.h"

extern t_malloc	g_info;

static size_t	get_new_page(size_t size)
{
  size_t	pages;

  pages = ((size / g_info.page_size) + 1) * g_info.page_size;
  if (!g_info.end_in_page)
  {
    if ((g_info.end_in_page = sbrk(0)) == (void*)-1)
      return ((size_t)-1);
    g_info.first_block = g_info.end_in_page;
  }
  if (sbrk(pages) == (void*)-1)
  {
    errno = ENOMEM;
    return ((size_t)-1);
  }
  return (pages);
}

static void	*get_in_page(size_t size)
{
  t_metadata	*new;

  new = g_info.end_in_page;
  new->size = size;
  new->free = NFREE;
  new->next = (t_metadata*)0;
  new->prev = g_info.last_node;
  if (g_info.last_node)
    g_info.last_node->next = new;
  g_info.last_node = new;
  g_info.end_in_page = (void*)new + size;
  return (new);
}

void		*get_heap(size_t size)
{
  size_t	tmp;

  if (g_info.page_remaining < size)
  {
    if ((tmp = get_new_page(size)) == (size_t)-1)
      return ((void*)0);
    g_info.page_remaining += tmp;
  }
  g_info.page_remaining -= size;
  return (get_in_page(size));
}
