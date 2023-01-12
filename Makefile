# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 12:39:14 by znichola          #+#    #+#              #
#    Updated: 2023/01/11 20:23:38 by znichola         ###   ########.fr        #
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

FILES		=	main tokenizer utils

SRCS		=	$(addprefix $(SRCS_PATH), $(addsuffix .c, $(FILES)))
OBJS		=	$(addprefix $(OBJS_PATH), $(addsuffix .o, $(FILES)))

# submodule
# libft
LIBFT_DIR		=	libft
LIBFT_N			=	libft.a
LIBFT			=	$(LIBFT_DIR)/$(LIBFT_N)

LIBS			=	-lft -lreadline
LIBS_PATH		=	-L$(LIBFT_DIR)

all		: $(NAME)

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c
	mkdir -p $(OBJS_PATH)
	$(CC) $(CFLAGS) -c -I$(INCS_PATH) -o $@ $<

$(NAME)	: $(LIB_N) $(OBJS)
	$(CC) $(CFLAGS) -I$(INCS_PATH) $(LIBS_PATH) $(LIBS) -o $@ $(OBJS)

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all
	$(MAKE) re -C $(LIBFT_DIR)

$(LIBFT_N):
		$(MAKE) -C $(LIBFT_DIR) $(LIBFT_N)
		cp $(LIBFT) $(NAME)

LIBMINISHELL	= libminishell.a

$(LIBMINISHELL): $(OBJS) $(LIBFT)
	cp $(LIBFT) libminishell.a
	ar rcs libminishell.a $(OBJS)

lib		: $(LIBMINISHELL)

.PHONY	: all clean fclean re
