# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 12:39:14 by znichola          #+#    #+#              #
#    Updated: 2023/01/27 12:08:00 by skoulen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET=\033[0m
BLUE=\033[34m
RED=\033[31m
GREEN=\033[32m
MAGENTA=\033[35m
YELLOW=\033[33m

NAME			=	minishell
LIBMINISHELL	=	libminishell.a

CC		=	gcc
CFLAGS	=	-Wall -Wextra
CFLAGS	+=	-Werror

# If DEBUG env variable is set, compile with debugging symbols
# and the compiler's address sanitizer
ifdef DEBUG
	CFLAGS	+=	-g3 -fsanitize=address
endif

RM		=	rm -rf

SRCS_PATH	=	srcs/
OBJS_PATH	=	objs/

BUILTINS		=	echo            pwd             env             exit      \
					shout           export          unset           cd

EXPANSION_FILES	=	var_exp         wild_exp        expansion                 \
					quote_removal   param_expansion expansion2      field_split

PARSING_FILES	=	prs_pipeline    prs_cmd         prs_item                  \
					parse_errors

SIGNALS_FILES	=	signals         termios

STRUCT_FILES	=	t_token         t_tree          t_word_lst      t_cmd     \
					t_cmd_info      t_tree_print    t_fds           t_item    \
					t_env           t_pipeline      t_parsed_cmd              \
					t_parsed_pipeline

EXECUTION_FILES	=	heredoc         find_cmd        find_cmd_utils  prep_cmds \
					prep_fds        exec_utils      mult_cmds                 \
					exec_builtin    exec_pipeline   simple_cmd                \
					launch_builtin

TOKENIZER_FILES	=	tokenizer       token_list

UTILS_FILES		=	utils_1         utils_2         tree_ops                  \
					error_printer

ENVIRONMENT		=	environment     env_utils       env_sort

BUILTINS		:=	$(addprefix builtins/,	$(BUILTINS))
EXPANSION_FILES	:=	$(addprefix expansion/, $(EXPANSION_FILES))
PARSING_FILES	:=	$(addprefix parsing/, 	$(PARSING_FILES))
SIGNALS_FILES	:=	$(addprefix signals/, 	$(SIGNALS_FILES))
STRUCT_FILES	:=	$(addprefix structs/, 	$(STRUCT_FILES))
EXECUTION_FILES	:=	$(addprefix execution/,	$(EXECUTION_FILES))
TOKENIZER_FILES	:=	$(addprefix tokenizer/,	$(TOKENIZER_FILES))
UTILS_FILES		:=	$(addprefix utils/,		$(UTILS_FILES))
ENVIRONMENT		:=	$(addprefix environment/, $(ENVIRONMENT))


FILES		=	main	$(BUILTINS) $(EXPANSION_FILES) $(PARSING_FILES)       \
						$(STRUCT_FILES) $(EXECUTION_FILES) $(TOKENIZER_FILES) \
						$(UTILS_FILES) $(ENVIRONMENT) $(SIGNALS_FILES)

SRCS		=	$(addprefix $(SRCS_PATH), $(addsuffix .c, $(FILES)))
OBJS		=	$(addprefix $(OBJS_PATH), $(addsuffix .o, $(FILES)))

# submodule
# libft
LIBFT_DIR	=	libft
LIBFT_N		=	libft.a
LIBFT		=	$(LIBFT_DIR)/$(LIBFT_N)

LIBS		=	-lft -lreadline

INCS_PATH	=	-Iincludes/
LIBS_PATH	=	-L$(LIBFT_DIR)

# If READLINE env variable is set, use it as an extra include and
# library path.
# This is useful if we cannot install readline in the compilers include
# directory.
ifdef READLINE
	LIBS_PATH += -L$(READLINE)/lib
	INCS_PATH	+= -I$(READLINE)/include
endif

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $(INCS_PATH) -o $@ $<

$(NAME)	: $(LIBFT) $(OBJS)
	@echo "$(GREEN)...compiling minishell...$(RESET)"
	@$(CC) $(CFLAGS) $(INCS_PATH) $(LIBS_PATH) $(LIBS) -o $@ $(OBJS)

$(LIBFT):
	@echo "$(BLUE)...building and archiving libft...$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR) $(LIBFT_N)
	@cp $(LIBFT) $(NAME)

run-tests : re
	@make run-tests -C unit-tests ; make run-tests -C unit-tests-builtins

clean	:
	@echo "$(YELLOW)...removing object files...$(RESET)"
	@$(RM) $(OBJS)
	@$(MAKE) -s clean -C $(LIBFT_DIR)

fclean	: clean
	@echo "$(YELLOW)...removing binaries...$(RESET)"
	@$(RM) $(NAME) $(LIBMINISHELL)
	@$(MAKE) -s fclean -C unit-tests
	@$(MAKE) -s fclean -C $(LIBFT_DIR)

re		: fclean all

.PHONY: all clean fclean re lib run-tests

# Rule to archive object files into a static library.
# Useful for unit testing
$(LIBMINISHELL): $(OBJS) $(LIBFT)
	@echo "$(MAGENTA)...archiving libminishell...$(RESET)"
	@cp $(LIBFT) $(LIBMINISHELL)
	@ar rcs $(LIBMINISHELL) $(OBJS)

lib: $(LIBMINISHELL)
