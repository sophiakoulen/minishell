# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 12:39:14 by znichola          #+#    #+#              #
#    Updated: 2023/01/18 16:45:52 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	gcc
CFLAGS	=	-Wall -Wextra
CFLAGS	+=	-Werror
CFLAGS	+=	-g3 -fsanitize=address
RM		=	rm -rf

INCS_PATH	=	includes/
SRCS_PATH	=	srcs/
OBJS_PATH	=	objs/

BUILTINS		=	echo            pwd             env             exit
EXPANSION_FILES	=	var_exp         wild_exp        expansion
PARSING_FILES	=	prs_pipeline    prs_cmd         prs_item                  \
					parse_errors
STRUCT_FILES	=	t_token         t_tree          t_word_lst      t_cmd     \
					t_cmd_info      t_tree_print    t_fds           t_item    \
					t_env           t_pipeline      t_parsed_cmd
EXECUTION_FILES	=	heredoc         find_cmd        find_cmd_utils  prep_cmds \
					prep_fds        exec_utils      mult_cmds                 \
					exec_builtin    exec_pipeline   simple_cmd
TOKENIZER_FILES	=	tokenizer       token_list
UTILS_FILES		=	utils_1         tree_ops

BUILTINS		:=	$(addprefix builtins/,	$(BUILTINS))
EXPANSION_FILES	:=	$(addprefix expansion/, $(EXPANSION_FILES))
PARSING_FILES	:=	$(addprefix parsing/, 	$(PARSING_FILES))
STRUCT_FILES	:=	$(addprefix structs/, 	$(STRUCT_FILES))
EXECUTION_FILES	:=	$(addprefix execution/,	$(EXECUTION_FILES))
TOKENIZER_FILES	:=	$(addprefix tokenizer/,	$(TOKENIZER_FILES))
UTILS_FILES		:=	$(addprefix utils/,		$(UTILS_FILES))

FILES		=	main	$(BUILTINS) $(EXPANSION_FILES) $(PARSING_FILES)       \
						$(STRUCT_FILES) $(EXECUTION_FILES) $(TOKENIZER_FILES) \
						$(UTILS_FILES)

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

run-tests : re
	@make run-tests -C unit-tests ; make run-tests -C unit-tests-builtins

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME) $(LIBMINISHELL)
	$(MAKE) fclean -C unit-tests

re		: fclean all
	$(MAKE) re -C $(LIBFT_DIR)

.PHONY	: all clean fclean re
