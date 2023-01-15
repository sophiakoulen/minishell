# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 12:39:14 by znichola          #+#    #+#              #
#    Updated: 2023/01/15 16:56:01 by skoulen          ###   ########.fr        #
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

PARSING_FILES	=	prs_commandline prs_pipeline prs_command prs_item
EXECUTION_FILES	=	heredoc find_cmd find_cmd_utils prepare_cmd prepare_fds
TOKENIZER_FILES	=	tokenizer
UTILS_FILES		=	utils_1 tree_ops
BUILTINS		=	echo pwd

PARSING_FILES	:=	$(addprefix parsing/, $(PARSING_FILES))
EXECUTION_FILES	:=	$(addprefix execution/, $(EXECUTION_FILES))
TOKENIZER_FILES	:=	$(addprefix tokenizer/, $(TOKENIZER_FILES))
UTILS_FILES		:=	$(addprefix utils/, $(UTILS_FILES))
BUILTINS		:=	$(addprefix builtins/, $(BUILTINS))

FILES		=	main $(PARSING_FILES) $(EXECUTION_FILES) $(TOKENIZER_FILES) $(UTILS_FILES) $(BUILTINS)

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
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -I$(INCS_PATH) -o $@ $<

$(NAME)	: $(LIB_N) $(OBJS)
	$(CC) $(CFLAGS) -I$(INCS_PATH) $(LIBS_PATH) $(LIBS) -o $@ $(OBJS)

$(LIBFT_N):
		$(MAKE) -C $(LIBFT_DIR) $(LIBFT_N)
		cp $(LIBFT) $(NAME)

# minishell library for unit tests
LIBMINISHELL	= libminishell.a

$(LIBMINISHELL): $(OBJS) $(LIBFT)
	cp $(LIBFT) libminishell.a
	ar rcs libminishell.a $(OBJS)

lib		: $(LIBMINISHELL)

# end minshell library

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME) $(LIBMINISHELL)
	$(MAKE) fclean -C unit-tests

re		: fclean all
	$(MAKE) re -C $(LIBFT_DIR)

.PHONY	: all clean fclean re
