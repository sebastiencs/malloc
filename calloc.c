/*
** calloc.c for epitech in /home/chapui_s/travaux/malloc/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Feb  2 15:52:40 2015 chapui_s
** Last update Sun Feb 15 19:31:43 2015 chapui_s
*/

#include "malloc.h"

extern t_malloc	g_info;

void	*calloc(size_t nmemb, size_t size)
{
  void	*ptr;

  if (nmemb == 0 || size == 0)
    return ((void*)0);
  if ((ptr = malloc(size * nmemb)) == (void*)0)
    return ((void*)0);
  pthread_mutex_lock(&(g_info.mutex));
  bzero(ptr, ALIGN_BYTES(size * nmemb));
  pthread_mutex_unlock(&(g_info.mutex));
  return (ptr);
}
