# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 13:03:20 by znichola          #+#    #+#              #
#    Updated: 2023/01/27 13:43:25 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	exp_wildcards

CFLAGS	=	-Wall -Wextra
CFLAGS	+=	-Werror

# If DEBUG env variable is set, compile with debugging symbols
# and the compiler's address sanitizer
ifdef DEBUG
	CFLAGS	+=	-g3 -fsanitize=address
endif

OBJS	=	wildcard_exp.o


all : $(NAME)

libft :
	$(MAKE) -C ../libft
	cp ../libft/libft.a .

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lft -L. -o $(NAME)

clean :
	$(RM) $(OBJS) $(NAME)
