# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 13:11:55 by znichola          #+#    #+#              #
#    Updated: 2023/01/18 10:27:15 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= builtin-tests

CC		= gcc
CFLAGS	= -Wall -Wextra
#CFLAGS += -Werror
CFLAGS += -g3 -fsanitize=address

TEST_NAMES	= echo pwd env

# put the unit test files here
# have one file that's the same as the test name
FILES		:= $(TEST_NAMES)

INCS_PATH	=	../includes/
OBJS_PATH	=	objs/
SRCS_PATH	=	srcs/
BIN_PATH	=	bin/

SRCS		=	$(addprefix $(SRCS_PATH), $(addsuffix _test.o, $(FILES)))
OBJS		=	$(addprefix $(OBJS_PATH), $(addsuffix _test.o, $(FILES)))
TST_SCRIPTS	=	$(addprefix run_, $(addsuffix _test.sh, $(TEST_NAMES)))

all: $(NAME)
	@mkdir -p bin

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -I$(INCS_PATH) -o $@ $<

#need to compile with the readline lib
$(NAME) : $(OBJS)
	$(MAKE) lib -C ..

run-tests : re
	@echo "\033[33m\n----------------------------\n Running builtin unit-tests\n----------------------------\n\033[0m"
	@for i in $(TST_SCRIPTS); do echo;"./$$i"; done

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(addsuffix .test, $(TEST_NAMES))

# Individual unit tests

echo : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

pwd : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

env : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

re: fclean all

.PHONY	: all clean fclean re
