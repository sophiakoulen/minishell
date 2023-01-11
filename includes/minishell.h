/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:31:34 by znichola          #+#    #+#             */
/*   Updated: 2023/01/11 19:49:30 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "stdio.h"
# include "libft.h"
# include "tokenizer.h"

/* tokenizer.c */



/* tokenizer.c */

const char	*ret_token_literal(enum e_token_type n);
t_token		*construct_tok_list(char *str);

/* utils.c */

void	*allocate(size_t size, size_t quantity);

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>



#endif
