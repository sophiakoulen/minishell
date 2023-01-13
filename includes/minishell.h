/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:34 by znichola          #+#    #+#             */
/*   Updated: 2023/01/13 16:17:42 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "libft.h"
# include "tokenizer.h"
# include "parsing.h"
# include "execution.h"


/* tokenizer.c */

const char	*ret_token_literal(enum e_token_type n);
t_token		*construct_tok_list(char *str);

/*  .... parsing .... */

t_token	*token_factory(t_token *next, char *str, enum e_token_type type);
t_tree	*tree_factory(t_tree *blueprint);

int	parse_commandline(t_tree **tree, t_token *tok);

int	parse_pipeline(t_tree **tree, t_token **tok);

int	parse_command(t_tree **tree, t_token **tok);

/* utils.c */

void	*x_malloc(size_t size, size_t quantity);

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>



#endif
