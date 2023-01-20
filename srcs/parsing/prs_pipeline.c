/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 08:14:59 by znichola          #+#    #+#             */
/*   Updated: 2023/01/20 12:00:08 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			create_parsed_cmd_list(t_list **lst, t_token **tok);
static t_parsed_cmd	**list_to_array(t_list *lst);

/*
	Parse a pipeline into an intermediate pipeline structure.

	Grammar rule:
	<pipeline> ::= <command>
            	| <command> '|' <pipeline>
*/
int	parse_pipeline(t_parsed_pipeline *pipeline, t_token **tok)
{
	t_list			*lst;

	*pipeline = (t_parsed_pipeline){0, NULL};
	if ((*tok)->type == e_end)
		return (STOP);
	lst = NULL;
	if (create_parsed_cmd_list(&lst, tok) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	*pipeline = (t_parsed_pipeline){ft_lstsize(lst), list_to_array(lst)};
	ft_lstclear(&lst, do_nothing);
	return (SUCCESS);
}

/*
	Parse encountered commands into a command list.
	Return SUCCESS or SYNTAX_ERROR.
*/
static int	create_parsed_cmd_list(t_list **lst, t_token **tok)
{
	t_parsed_cmd	*cmd;
	int				ret;

	ret = parse_cmd(&cmd, tok);
	while (ret == 0)
	{
		ft_lstadd_back(lst, ft_lstnew(cmd));
		if ((*tok)->type == e_end)
			break ;
		if (assert_token(*tok, e_pipe) != SUCCESS)
		{
			ret = SYNTAX_ERROR;
			break ;
		}
		next_token(tok);
		ret = parse_cmd(&cmd, tok);
	}
	if (!*lst)
		return (unexpected_token(*tok));
	if (ret == SYNTAX_ERROR)
	{
		ft_lstclear(lst, (void (*)(void *))parsed_cmd_cleanup);
		return (SYNTAX_ERROR);
	}
	return (SUCCESS);
}

/*
	Translate a list of t_parsed_commands into an array.
*/
static t_parsed_cmd	**list_to_array(t_list *lst)
{
	t_parsed_cmd	**array;
	int				size;
	int				i;

	size = ft_lstsize(lst);
	array = x_malloc(sizeof(*array), size);
	i = 0;
	while (lst)
	{
		array[i] = lst->content;
		lst = lst->next;
		i++;
	}
	return (array);
}
