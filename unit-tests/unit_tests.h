/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_tests.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:33:19 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/15 08:41:34 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNIT_TESTS_H
# define UNIT_TESTS_H

# include "minishell.h"

/**
 * Screen posiiton struct.
 */
typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;


/* tokenizer tests */

void	print_token_list_minimal(t_token *tok);
void	auto_print_tree(t_tree *tree);

#endif
