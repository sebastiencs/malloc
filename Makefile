##
## Makefile for epitech in /home/chapui_s/travaux/malloc_ok/Makefile
## 
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
## 
## Started on  Sun Feb 15 19:58:32 2015 chapui_s
## Last update Sat Feb 21 19:33:09 2015 chapui_s
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

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo -e "\033[0;032m[$(NAME)] Compiled\033[0;0m"
		ln -fs $(NAME) libmy_malloc.so
		@echo -e "\033[0;032m[libmy_malloc.so] Link created\033[0;0m"

all:		$(NAME)

clean:
		@echo -e "\033[0;031m[clean] " | tr -d '\n'
		rm -f $(OBJ)
		@echo -e "\033[0;0m" | tr -d '\n'

fclean:		clean
		@echo -e "\033[0;031m[fclean] " | tr -d '\n'
		rm -f $(NAME)
		$(RM) libmy_malloc.so
		@echo -e "\033[0;0m" | tr -d '\n'

re:		fclean all

.PHONY:		all clean fclean re
