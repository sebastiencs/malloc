##
## Makefile for epitech in /home/chapui_s/travaux/malloc_ok/Makefile
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Sun Feb 15 19:58:32 2015 chapui_s
## Last update Sun Feb 15 23:30:33 2015 chapui_s
##

ifndef HOSTTYPE
HOSTTYPE	= $(shell uname -i)
endif

NAME		= libmy_malloc_$(HOSTTYPE).so

SRC		= malloc.c		\
		  free.c		\
		  calloc.c		\
		  realloc.c		\
		  fusion.c		\
		  get_heap.c		\
		  show_alloc_mem.c	\
		  rbtree/insert.c	\
		  rbtree/rotate.c	\
		  rbtree/insert_utils.c	\
		  rbtree/remove.c	\
		  rbtree/flip_color.c	\
		  rbtree/remove_utils.c

OBJ		= $(SRC:.c=.o)

CFLAGS		+= -O3 -Wall -Wextra -fPIC -shared -I .

CC		= gcc

RM		= rm -f

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		ln -fs $(NAME) libmy_malloc.so

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)
		$(RM) libmy_malloc.so

re:		fclean all

.PHONY:		all clean fclean re
