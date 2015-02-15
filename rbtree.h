/*
** rbtree.h for rbtree in /home/chapuis_s/rendu/rbtree
**
** Made by chapui_s
** Login   <chapui_s@epitech.eu>
**
** Started on  Mon Jan 26 19:41:38 2015 chapui_s
** Last update Sun Feb 15 23:17:13 2015 chapui_s
*/

#ifndef RBTREE_H_
# define RBTREE_H_

# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>

typedef enum	rbcolor
{
  BLACK = 0,
  RED = 1
}		t_rbcolor;

typedef struct		s_metadata
{
  size_t		size;
  size_t		free;
  struct s_metadata	*next;
  struct s_metadata	*prev;
}			t_metadata;

typedef size_t		t_key;
typedef t_metadata	t_value;

typedef struct		s_rbnode
{
  size_t		size;
  size_t		free;
  t_metadata		*next;
  t_metadata		*prev;
  t_key			key;
  t_value		**tab_values;
  size_t		size_tab;
  size_t		nb_activ;
  t_rbcolor		color;
  struct s_rbnode	*left;
  struct s_rbnode	*right;
}			t_rbnode;

typedef struct		s_malloc
{
  t_rbnode		*root_rbtree;
  t_metadata		*last_node;
  void			*end_in_page;
  void			*first_block;
  int			page_size;
  pthread_mutex_t	mutex;
  size_t		page_remaining;
}			t_malloc;

# ifdef __x86_64__
#  define YFREE			0xDEADBEEF5EBA571E
#  define NFREE			0x5EBA571EDEADBEEF
#  define ALIGN_BYTES(x)	((((x - 1) >> 4) << 4) + 16)
# else /* !__x86_64__ */
#  define YFREE			0x5EBA571E
#  define NFREE			0xDEADBEEF
#  define ALIGN_BYTES(x)	((((x - 1) >> 3) << 3) + 8)
# endif /* !__x86_64__ */

# define SIZE_TAB_VALUES	(256)
# define META_SIZE		ALIGN_BYTES((sizeof(t_metadata)))
# define GET_PAYLOAD(x)		((void*)((size_t)x + META_SIZE))
# define GET_NODE(x)		((void*)((size_t)x - META_SIZE))
# define SIZE_DEFAULT_BLOCK	(32)
# define IS_VALID(x)		(((t_metadata*)x)->free == YFREE \
				 || ((t_metadata*)x)->free == NFREE)
# define IS_FREE(x)		((x) ? (((t_metadata*)x)->free == YFREE) : (0))
# define IS_RED(x)		((x) ? (((t_rbnode*)x)->color == RED) : (0))
# define MY_COMPARE(k1, k2)	(((k1 == k2) ? (0) : ((k1 < k2) ? (-1) : (1))))

extern const char *__progname;

t_rbnode	*remove_from_freed_list(t_rbnode *root_rbtree,
					t_metadata *meta);
t_rbnode	*insert_in_freed_list(t_rbnode *node, t_metadata *new);
void		*get_heap(size_t size);
void		*calloc(size_t nmemb, size_t size);
void		*realloc(void *ptr, size_t size);
t_metadata	*fusion(t_metadata *first, t_metadata *second);
void		flip_color(t_rbnode *node);
t_rbnode	*rotate_left(t_rbnode *node);
t_rbnode	*rotate_right(t_rbnode *node);
t_rbnode	*new_rbtree(t_metadata *node);
int		resize_tab_values(t_metadata **old, t_rbnode *node);
void		flip_color(t_rbnode *node);
t_rbnode	*get_key(t_rbnode *node, t_key key);
t_rbnode	*min(t_rbnode *node);
t_rbnode	*balance_me_that(t_rbnode *node);
t_rbnode	*move_red_to_left(t_rbnode *node);
t_rbnode	*move_red_to_right(t_rbnode *node);
void		flip_color(t_rbnode *node);
t_rbnode	*remove_key(t_rbnode *node, t_key key);

#endif /* !RBTREE_H_ */
