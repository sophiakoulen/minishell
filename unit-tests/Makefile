# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:33:05 by skoulen           #+#    #+#              #
#    Updated: 2023/01/18 09:47:14 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= test

CC		= gcc
CFLAGS	= -Wall -Wextra
# CFLAGS += -Werror
# CFLAGS += -g3 -fsanitize=address

TEST_NAMES	=	tokenizer    parsing      heredoc      parse_item   prepare_cmd \
				mult_cmd     prs_cmd      prs_pipeline

# put the unit test files here
# have one file that's the same as the test name
FILES		:= $(TEST_NAMES)

INCS_PATH	=	../includes/
OBJS_PATH	=	objs/
SRCS_PATH	=	srcs/
BIN_PATH	=	bin/

SRCS		=	$(addprefix $(SRCS_PATH), $(addsuffix _test.c, $(FILES)))
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

run_tests :
	@for i in $(TST_SCRIPTS); do "./$$i"; done

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(addsuffix .test, $(BIN_PATH)$(TEST_NAMES))

# Individual unit tests

tokenizer : all
	$(CC) $(CFLAGS) -I../../includes -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

parsing : all
	$(CC) $(CFLAGS) -I../../includes -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

heredoc : all
	$(CC) $(CFLAGS) -I../../includes -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

parse_item : all
	$(CC) $(CFLAGS) -I../../includes -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o
prepare_cmd : all
	$(CC) $(CFLAGS) -I../../includes -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

mult_cmd : all
	$(CC) $(CFLAGS) -I../../includes -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

prs_cmd : all
	$(CC) $(CFLAGS) -I../../includes -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

prs_pipeline : all
	$(CC) $(CFLAGS) -I../../includes -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

re: fclean all

.PHONY	: all clean fclean re
