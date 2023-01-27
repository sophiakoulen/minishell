# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 13:03:20 by znichola          #+#    #+#              #
#    Updated: 2023/01/27 13:20:10 by znichola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	exp_wildcards

OBJS	=	wildcard_exp.o

all : $(NAME)

libft :
	$(MAKE) -C ../libft
	cp ../libft/libft.a .

$(NAME) : $(OBJS)
	$(CC)  $(OBJS) -lft -L. -o $(NAME)

clean :
	$(RM) $(OBJS) $(NAME)
