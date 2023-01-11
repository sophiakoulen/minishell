# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:33:05 by skoulen           #+#    #+#              #
#    Updated: 2023/01/12 00:09:05 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= test

CC		= gcc
CFLAGS	= -Wall -Wextra
CFLAGS += -Werror

# put the unit test files here
SRCS	= test_1.c

all: $(NAME)

.c.o :
		$(CC) $(CFLAGS) -I../includes -c $< -o $(@)

#need to compile with the readline lib
$(NAME) : $(SRCS)
	$(MAKE) lib -C ..
#	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@ $(SRCS)

fclean :
	rm -f test

# Individual unit tests

test_tokenizer : all test_tokenizer.o
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@ $@.o
#	./$@ "this is a test"
# make test_tokenizer && ./test_tokenizer "&&||< >>>| some_test && more  ||  make test_tokenizer"

re: fclean all
