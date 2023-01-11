# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:33:05 by skoulen           #+#    #+#              #
#    Updated: 2023/01/11 15:58:06 by skoulen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= test

CC		= gcc
CFLAGS	= -Wall -Wextra
CFLAGS += -Werror

# put the unit test files here
SRCS	= test_1.c

all: $(NAME)

#need to compile with the readline lib
$(NAME): $(SRCS)
	$(MAKE) lib -C ..
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@ $(SRCS)

fclean:
	rm -f test

re: fclean all
