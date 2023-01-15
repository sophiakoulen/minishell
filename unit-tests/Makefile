# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:33:05 by skoulen           #+#    #+#              #
#    Updated: 2023/01/15 16:57:23 by skoulen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= test

CC		= gcc
CFLAGS	= -Wall -Wextra
#CFLAGS += -Werror
CFLAGS += -g3 -fsanitize=address

TEST_NAMES	= tokenizer parsing heredoc parse_item prepare_cmd mult_cmd

# put the unit test files here
# have one file that's the same as the test name
FILES		:= $(TEST_NAMES) print_tree

OBJS_PATH	=	objs/

OBJS		=	$(addprefix $(OBJS_PATH), $(addsuffix _test.o, $(FILES)))


all: $(NAME)

$(OBJS_PATH)%.o : %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I../includes -c $< -o $(@)

#need to compile with the readline lib
$(NAME) : $(OBJS)
	$(MAKE) lib -C ..

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(addsuffix .test, $(TEST_NAMES))

# Individual unit tests

tokenizer : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $(OBJS_PATH)$@_test.o

parsing : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $(OBJS_PATH)$@_test.o $(OBJS_PATH)print_tree_test.o

heredoc : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $(OBJS_PATH)$@_test.o

parse_item : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $(OBJS_PATH)$@_test.o $(OBJS_PATH)print_tree_test.o

prepare_cmd : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $(OBJS_PATH)$@_test.o

mult_cmd : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $(OBJS_PATH)$@_test.o

re: fclean all

.PHONY	: all clean fclean re
