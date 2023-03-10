# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 12:39:14 by znichola          #+#    #+#              #
#    Updated: 2023/02/16 22:48:37 by znichola         ###   ########.fr        #
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
CFLAGS	+=	-Werror -g

# If DEBUG env variable is set, compile with debugging symbols
# and the compiler's address sanitizer
ifdef DEBUG
	CFLAGS	+=	-g3 -fsanitize=address
endif

RM		=	rm -rf

SRCS_PATH	=	srcs/
OBJS_PATH	=	objs/

BUILTINS		=	echo             pwd             env             exit      \
					shout            export          unset           cd        \
					minitree

EXPANSION_FILES	=	quote_removal    param_expansion field_split               \
					expansion        expansion_utils wildcard_exp              \
					wildcard_wrapper wild_split      wildcard_match

PARSING_FILES	=	prs_pipeline     prs_cmd         prs_item                  \
					parse_errors     prs_tree

SIGNALS_FILES	=	signals          termios         signals_msg

STRUCT_FILES	=	t_token          t_tree          t_cmd           t_exec    \
					t_tree_print                     t_item                    \
					t_env            t_trunk

EXECUTION_FILES	=	prep_pipeline    prep_utils                                \
					exec_pipeline    exec_pipeline2  exec_utils                \
					find_cmd                                                   \
					builtin          heredoc

TOKENIZER_FILES	=	tokenizer        token_list

UTILS_FILES		=	utils_1          utils_2         tree_ops         input    \
					error_printer    lst_sort        safe_atoi        print    \
					cleanup

ENVIRONMENT		=	env_init         env_utils       env_utils2       env_sort

BUILTINS		:=	$(addprefix builtins/,	$(BUILTINS))
EXPANSION_FILES	:=	$(addprefix expansion/, $(EXPANSION_FILES))
PARSING_FILES	:=	$(addprefix parsing/, 	$(PARSING_FILES))
SIGNALS_FILES	:=	$(addprefix signals/, 	$(SIGNALS_FILES))
STRUCT_FILES	:=	$(addprefix structs/, 	$(STRUCT_FILES))
EXECUTION_FILES	:=	$(addprefix execution/,	$(EXECUTION_FILES))
TOKENIZER_FILES	:=	$(addprefix tokenizer/,	$(TOKENIZER_FILES))
UTILS_FILES		:=	$(addprefix utils/,		$(UTILS_FILES))
ENVIRONMENT		:=	$(addprefix environment/, $(ENVIRONMENT))


FILES			=	main	$(BUILTINS)        $(EXPANSION_FILES) \
							$(PARSING_FILES)   $(STRUCT_FILES)    \
							$(EXECUTION_FILES) $(TOKENIZER_FILES) \
							$(UTILS_FILES)     $(ENVIRONMENT)     \
							$(SIGNALS_FILES)

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
	@$(CC) $(CFLAGS) $(OBJS) $(INCS_PATH) $(LIBS_PATH) $(LIBS) -o $@

$(LIBFT):
	@echo "$(BLUE)...building and archiving libft...$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR) $(LIBFT_N)
	@cp $(LIBFT) $(NAME)

run-tests :
	@printf "\n$(YELLOW)checking the norminette ... "
	@norminette 1>/dev/null && printf "$(GREEN)OK" || printf "$(RED)KO" ; printf "$(RESET)\n"
	@make run-tests -C tests-unit ; make run-tests -C tests-builtins ; tests-functional/launch_tests.sh

clean	:
	@echo "$(YELLOW)...removing object files...$(RESET)"
	@$(RM) $(OBJS)

fclean	: clean
	@echo "$(YELLOW)...removing binaries...$(RESET)"
	@$(RM) $(NAME) $(LIBMINISHELL)
	@$(MAKE) -s fclean -C $(LIBFT_DIR)

re		: fclean all

CURRENT_DIR = $(shell pwd)

docker : fclean
	echo $(CURRENT_DIR)
#	docker run -it -v /Users/znichola/Documents/minishell:/minishell minishell_docker_image
	docker run -it -v $(CURRENT_DIR):/minishell minishell_docker_image

dockerbuild :
	docker build -t minishell_docker_image .

.PHONY: all clean fclean re lib run-tests

# Rule to archive object files into a static library.
# Useful for unit testing
$(LIBMINISHELL): $(OBJS) $(LIBFT)
	@echo "$(MAGENTA)...archiving libminishell...$(RESET)"
	@cp $(LIBFT) $(LIBMINISHELL)
	@ar rcs $(LIBMINISHELL) $(OBJS)

lib: $(LIBMINISHELL)
