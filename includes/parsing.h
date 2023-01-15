/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:14:07 by znichola          #+#    #+#             */
/*   Updated: 2023/01/15 18:26:38 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "tokenizer.h"

typedef struct s_tree
{
	enum e_token_type	type;
	char				*str;
	struct s_tree		*left;
	struct s_tree		*right;
}	t_tree;

typedef struct s_word_lst
{
	char				*str;
	struct s_word_lst	*next;
}	t_word_lst;

#endif
