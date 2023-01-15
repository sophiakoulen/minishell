# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 13:11:55 by znichola          #+#    #+#              #
#    Updated: 2023/01/15 15:32:38 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= builtins

CC		= gcc
CFLAGS	= -Wall -Wextra
CFLAGS += -Werror

TEST_NAMES	= echo pwd

# put the unit test files here
# have one file that's the same as the test name
FILES		:= $(TEST_NAMES)

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

echo : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $(OBJS_PATH)$@_test.o

pwd : all
	$(CC) $(CFLAGS) -I../includes -lreadline -lminishell -L.. -o $@.test $(OBJS_PATH)$@_test.o

re: fclean all

.PHONY	: all clean fclean re
