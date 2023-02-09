# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:33:05 by skoulen           #+#    #+#              #
#    Updated: 2023/02/09 18:10:51 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET=\033[0m
BLUE=\033[34m
RED=\033[31m
GREEN=\033[32m
MAGENTA=\033[35m
YELLOW=\033[33m

NAME	= unit-tests

CC		= gcc
CFLAGS	= -Wall -Wextra
ifdef DEBUG
	CFLAGS += -g3 -fsanitize=address
endif

TEST_NAMES	=	param_expansion tokenizer       parsing         quote_removal  \
				field_split     wildcard_exp

DEV_NAMES	=	mult_cmd        heredoc         parse_item      prepare_cmd    \
				expansion       prs_cmd         wild_split

# put the unit test files here
# have one file that's the same as the test name
FILES		:= $(TEST_NAMES) $(DEV_NAMES)

INCS_PATH	=	../includes/
OBJS_PATH	=	objs/
SRCS_PATH	=	srcs/
BIN_PATH	=	bin/

SRCS		=	$(addprefix $(SRCS_PATH), $(addsuffix _test.c, $(FILES)))
OBJS		=	$(addprefix $(OBJS_PATH), $(addsuffix _test.o, $(FILES)))
TESTS		=	$(addprefix $(BIN_PATH), $(addsuffix .test, $(TEST_NAMES)))
TST_SCRIPTS	=	$(addprefix run_, $(addsuffix _test.sh, $(TEST_NAMES)))

all: run-tests

libminishell:
	@$(MAKE) lib -C ..

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -I$(INCS_PATH) -o $@ $<

#need to compile with the readline lib

run-tests : $(TESTS)
	@echo "\033[33m\n--------------------\n Running unit-tests\n--------------------\n\033[0m"
	@for i in $(TST_SCRIPTS); do echo;"./$$i"; done

clean :
	@echo "$(YELLOW)...removing object files...$(RESET)"
	@$(RM) $(OBJS)

fclean : clean
	@echo "$(YELLOW)...removing binaries...$(RESET)"
	@$(RM) $(addsuffix .test, $(BIN_PATH)$(TEST_NAMES))

re: fclean all

.PHONY	: all clean fclean re

# Individual unit tests
$(BIN_PATH)%.test: $(OBJS_PATH)%_test.o libminishell
	@mkdir -p bin
	$(CC) $(CFLAGS) $< -I$(INCS_PATH) -lreadline -lminishell -L.. -o $@

parsing: $(BIN_PATH)parsing.test

tokenizer: $(BIN_PATH)tokenizer.test

heredoc: $(BIN_PATH)heredoc.test

parse_item: $(BIN_PATH)parse_item.test

prepare_cmd: $(BIN_PATH)prepare_cmd.test

mult_cmd: $(BIN_PATH)mult_cmd.test

prs_cmd: $(BIN_PATH)prs_cmd.test

quote_removal: $(BIN_PATH)quote_removal.test

param_expansion: $(BIN_PATH)param_expansion.test

expansion: $(BIN_PATH)expansion.test

wildcard_exp: $(BIN_PATH)wildcard_exp.test

field_split: $(BIN_PATH)field_split.test

wild_split: $(BIN_PATH)wild_split.test
