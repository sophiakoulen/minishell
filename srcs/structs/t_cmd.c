/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:29:17 by znichola          #+#    #+#             */
/*   Updated: 2023/01/17 16:27:21 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args_array(char **args);
static void	print_redirs(t_list *redirs);
static void	cleanup_strs(char **strs);

/**
 * cmd_factory(&(t_tree){args, in, out})
 * call with blueprint or NULL
 * Don't forget to free it after!
*/
t_cmd	*cmd_factory(t_cmd *blueprint)
{
	t_cmd	*ret;

	ret = (t_cmd *)x_malloc(sizeof(t_cmd), 1);
	if (blueprint == NULL)
	{
		ret->args = NULL;
		ret->redirs = NULL;
	}
	else
	{
		ret->args= blueprint->args;
		ret->redirs = blueprint->redirs;
	}
	return (ret);
}
/*
	Frees the malloced content of cmd, not cmd itself!

	Used by pipeline_cleanup().

	args should contain strduped words i think, not the same
	pointers as in the token_list.

	redirs contains copies of items so they should be malloced,
	strings contained in the items should be strduped so freed also.
*/
void	cmd_cleanup(t_cmd *cmd)
{
	cleanup_strs(cmd->args);
	cmd->args = 0;
	ft_lstclear(&cmd->redirs, item_cleanup_deep);
}

void	print_cmd(t_cmd *cmd)
{
	ft_printf("CMD\n");
	if (!cmd)
	{
		ft_printf("(NULL)\n");
	}
	else
	{
		ft_printf("~~args~~\n");
		print_args_array(cmd->args);
		ft_printf("~~redirs~~\n");
		print_redirs(cmd->redirs);
	}
}

static void	print_args_array(char **args)
{
	int	count;

	if (!args)
	{
		ft_printf("\t(NULL)\n");
		return ;
	}
	count = 0;
	while(*args)
	{
		ft_printf("%2d. %s\n", count, *args);
		args++;
		count++;
	}
}

static void	print_redirs(t_list *redirs)
{
	while (redirs)
	{
		print_item(redirs->content);
		redirs = redirs->next;
	}
}

static void	cleanup_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs);
		i++;
	}
	free(strs);
}
