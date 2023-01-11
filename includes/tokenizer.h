/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:54:08 by znichola          #+#    #+#             */
/*   Updated: 2023/01/11 15:08:46 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

#include "minishell.h"

enum e_token_type
{
	e_string,
	e_symbol,
};

typedef struct s_token
{
	enum e_token_type	type;
	struct s_token		*next;
}	t_token;

#endif
