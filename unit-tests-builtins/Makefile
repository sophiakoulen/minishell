# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 13:11:55 by znichola          #+#    #+#              #
#    Updated: 2023/01/18 09:49:55 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= builtins

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

OBJS		=	$(addprefix $(OBJS_PATH), $(addsuffix _test.o, $(FILES)))
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

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(addsuffix .test, $(TEST_NAMES))

# Individual unit tests

echo : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $(OBJS_PATH)$@_test.o

pwd : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $(OBJS_PATH)$@_test.o

env : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $(OBJS_PATH)$@_test.o

re: fclean all

.PHONY	: all clean fclean re
