/*
** show_alloc_mem.c for epitech in /home/chapui_s/travaux/malloc/
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Sun Feb 15 19:56:20 2015 chapui_s
** Last update Sun Feb 15 23:08:53 2015 chapui_s
*/

#include "malloc.h"

extern t_malloc	g_info;

void		show_alloc_mem(void)
{
  t_metadata	*tmp;

  tmp = g_info.first_block;
  printf("break : %p\n", sbrk(0));
  while (tmp)
  {
    if (tmp->free == NFREE)
#ifdef __x86_64__
      printf("%p - %p : %lu octets\n",
#else /* !__x86_64__ */
      printf("%p - %p : %d octets\n",
#endif /* !__x86_64__ */
	     GET_PAYLOAD(tmp),
	     (GET_PAYLOAD(tmp) + tmp->size - META_SIZE),
	     tmp->size - META_SIZE);
    tmp = tmp->next;
  }
}
