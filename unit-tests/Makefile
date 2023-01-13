# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:33:05 by skoulen           #+#    #+#              #
#    Updated: 2023/01/13 11:33:24 by skoulen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=test

CC		= gcc
CFLAGS	= -Wall -Wextra
CFLAGS += -Werror

# put the unit test files here
FILES	= tokenizer parsing heredoc

OBJS	=	$(addsuffix _test.o, $(FILES))

all: $(NAME)

.c.o :
	$(CC) $(CFLAGS) -I../includes -c $< -o $(@)

#need to compile with the readline lib
$(NAME) : $(OBJS)
	$(MAKE) lib -C ..

clean :
	$(RM) *.test
	$(RM) $(OBJS)

fclean : clean
	$(RM) ../libminishell.a


# Individual unit tests

tokenizer : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $@_test.o

parsing : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $@_test.o

heredoc : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $@_test.o

re: fclean all

.PHONY	: all clean fclean re
