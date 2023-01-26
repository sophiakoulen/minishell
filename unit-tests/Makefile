# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 15:33:05 by skoulen           #+#    #+#              #
#    Updated: 2023/01/26 11:28:54 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= unit-tests

CC		= gcc
CFLAGS	= -Wall -Wextra
ifdef DEBUG
	CFLAGS += -g3 -fsanitize=address
endif

TEST_NAMES	=	param_expansion prs_cmd         prs_pipeline    quote_removal  \
				tokenizer
DEV_NAMES	=	mult_cmd        heredoc         parse_item      prepare_cmd    \
				expansion

# put the unit test files here
# have one file that's the same as the test name
FILES		:= $(TEST_NAMES)  $(DEV_NAMES)

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
	@$(MAKE) lib -C ..

run-tests : re
	@echo "\033[33m\n--------------------\n Running unit-tests\n--------------------\n\033[0m"
	@for i in $(TST_SCRIPTS); do echo;"./$$i"; done

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(addsuffix .test, $(BIN_PATH)$(TEST_NAMES))

# Individual unit tests

tokenizer : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

heredoc : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

parse_item : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

prepare_cmd : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

mult_cmd : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

prs_cmd : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

prs_pipeline : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

quote_removal : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

param_expansion : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

expansion : all
	$(CC) $(CFLAGS) -I$(INCS_PATH) -lreadline -lminishell -L.. -o $(BIN_PATH)$@.test $(OBJS_PATH)$@_test.o

re: fclean all

.PHONY	: all clean fclean re
