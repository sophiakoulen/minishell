NAME	= test

CC		= gcc
CFLAGS	= -Wall -Wextra
CFLAGS += -Werror

# put the unit test files here
SRCS	= test_1.c

all: $(NAME)

$(NAME): $(SRCS)
	$(MAKE) lib -C ..
	$(CC) $(CFLAGS) -I../includes -lminishell -L.. -o $@ $(SRCS)

fclean:
	rm -f test

re: fclean all
