/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:14:59 by znichola          #+#    #+#             */
/*   Updated: 2023/02/10 12:50:10 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			create_pipeline(t_list **pipeline, t_token **tok);

/*
	Parse a pipeline into an intermediate pipeline structure.

	Grammar rule:
	<pipeline> ::= <command>
            	| <command> '|' <pipeline>
*/
int	parse_pipeline(t_list **pipeline, t_token **tok)
{
	*pipeline = NULL;
	if ((*tok)->type == e_end)
	{
		unexpected_token(*tok);
		return (SYNTAX_ERROR);
	}
	if (create_pipeline(pipeline, tok) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	return (SUCCESS);
}

/*
	Parse encountered commands into a command list.
	Return SUCCESS or SYNTAX_ERROR.
*/
static int	create_pipeline(t_list **pipeline, t_token **tok)
{
	t_item	*cmd;
	int		ret;

	ret = parse_cmd(&cmd, tok);
	while (ret == 0)
	{
		ft_lstadd_back(pipeline, ft_lstnew(cmd));
		if ((*tok)->type == e_end || (*tok)->type == e_and
			|| (*tok)->type == e_or || (*tok)->type == e_close_brace)
			break ;
		if (assert_token(*tok, e_pipe) != SUCCESS)
		{
			ret = SYNTAX_ERROR;
			break ;
		}
		next_token(tok);
		ret = parse_cmd(&cmd, tok);
	}
	if (ret == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (!*pipeline)
		return (unexpected_token(*tok));
	return (SUCCESS);
}
