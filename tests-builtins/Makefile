# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 13:11:55 by znichola          #+#    #+#              #
#    Updated: 2023/02/16 20:36:05 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SECONDARY:

RESET=\033[0m
BLUE=\033[34m
RED=\033[31m
GREEN=\033[32m
MAGENTA=\033[35m
YELLOW=\033[33m

NAME	= builtin-tests

CC		= gcc
CFLAGS	= -Wall -Wextra
#CFLAGS += -Werror
CFLAGS += -g3 -fsanitize=address

TEST_NAMES	=	echo pwd env
DEV_NAMES	=	exprt

# put the unit test files here
# have one file that's the same as the test name
FILES		:= $(TEST_NAMES) $(DEV_NAMES)


INCS_PATH	=	../includes/
OBJS_PATH	=	objs/
SRCS_PATH	=	srcs/
BIN_PATH	=	bin/

SRCS		=	$(addprefix $(SRCS_PATH), $(addsuffix _test.o, $(FILES)))
OBJS		=	$(addprefix $(OBJS_PATH), $(addsuffix _test.o, $(FILES)))
TST_SCRIPTS	=	$(addprefix run_, $(addsuffix _test.sh, $(TEST_NAMES)))

all: $(OBJS)

libminishell:
	@$(MAKE) lib -C ..

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -I$(INCS_PATH) -o $@ $<

run-tests : re
	@echo "\033[33m\n----------------------------\n Running builtin unit-tests\n----------------------------\n\033[0m"
	@for i in $(TST_SCRIPTS); do echo;"./$$i"; done

clean :
	@echo "$(YELLOW)...removing unit-test object files...$(RESET)"
	$(RM) $(OBJS)

fclean : clean
	@echo "$(YELLOW)...removing unit-test binaries...$(RESET)"
	$(RM) $(addprefix $(BIN_PATH), $(addsuffix .test, $(TEST_NAMES)))

# Individual unit tests
$(BIN_PATH)%.test: $(OBJS_PATH)%_test.o libminishell
	@mkdir -p bin
	$(CC) $(CFLAGS) $< -I$(INCS_PATH) -lreadline -lminishell -L.. -o $@

echo: $(BIN_PATH)echo.test

pwd: $(BIN_PATH)pwd.test

env: $(BIN_PATH)env.test

exprt: $(BIN_PATH)exprt.test


re: fclean all

.PHONY	: all clean fclean re
