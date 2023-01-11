# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 12:39:14 by znichola          #+#    #+#              #
#    Updated: 2023/01/11 15:21:20 by skoulen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	gcc
# CFLAGS	=	-Wall -Werror -Wextra
CFLAGS	=	-Wall -Wextra
RM		=	rm -rf

INCS_PATH	=	includes/
SRCS_PATH	=	srcs/
OBJS_PATH	=	objs/

FILES		=	test main

SRCS		=	$(addprefix $(SRCS_PATH), $(addsuffix .c, $(FILES)))
OBJS		=	$(addprefix $(OBJS_PATH), $(addsuffix .o, $(FILES)))

# submodule
# libft
LIB_DIR		=	libft
LIB_N		=	libft.a
LIB			=	$(LIB_DIR)/$(LIB_N)

all		: $(NAME)

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c
	mkdir -p $(OBJS_PATH)
	$(CC) $(CFLAGS) -c -I$(INCS_PATH) -o $@ $<

$(NAME)	: $(LIB_N) $(OBJS)
	$(CC) $(CFLAGS) -I$(INCS_PATH) -o $@ $(OBJS) -L$(LIB_DIR) -lft

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

#TODO: change this before handin!
re		: fclean all

relib	: re
	$(MAKE) -C $(LIB_DIR) fclean

$(LIB_N):
		$(MAKE) -C $(LIB_DIR) $(LIB_N)
		cp $(LIB) $(NAME)

LIBMINISHELL	= libminishell.a

$(LIBMINISHELL): $(OBJS) $(LIB)
	cp $(LIB) libminishell.a
	ar rcs libminishell.a $(OBJS)

lib		: $(LIBMINISHELL)

.PHONY	: all clean fclean re
