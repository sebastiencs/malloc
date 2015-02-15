/*
** malloc.c for epitech in /home/chapui_s/travaux/malloc/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Feb  2 15:52:40 2015 chapui_s
** Last update Sun Feb 15 23:07:01 2015 chapui_s
*/

#include "malloc.h"

extern t_malloc	g_info;

void		*free_realloc(void *ptr)
{
  free(ptr);
  return ((void*)0);
}

void		*realloc(void *ptr, size_t size)
{
  t_metadata	*new;
  t_metadata	*tmp;

  if (!ptr)
    return (malloc(size));
  if (!size)
    return (free_realloc(ptr));
  ptr = (void*)ptr - META_SIZE;
  tmp = (t_metadata*)ptr;
  new = ptr;
  if (size + META_SIZE > tmp->size)
  {
    if ((new = malloc(size)) == (void*)0)
      return ((void*)0);
    size = ALIGN_BYTES(size);
    pthread_mutex_lock(&(g_info.mutex));
    memcpy(new, (void*)ptr + META_SIZE, (size <= tmp->size) ?
	   (size) : (tmp->size));
    pthread_mutex_unlock(&(g_info.mutex));
    free((void*)ptr + META_SIZE);
  }
  else
    new = GET_PAYLOAD(new);
  return (new);
}
