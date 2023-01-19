/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_parsed_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:08:07 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/19 18:10:44 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_redirs(t_list *redirs);
static void	print_args_list(t_list *args);
static void	print_redirs2(t_list *redirs);
static void	print_args_list2(t_list *args);

t_parsed_cmd 	*parsed_cmd_factory(t_parsed_cmd *blueprint)
{
	t_parsed_cmd *cmd;

	cmd = x_malloc(sizeof(*cmd), 1);
	if (blueprint)
	{
		cmd->args = blueprint->args;
		cmd->redirs = blueprint->redirs;
	}
	else
	{
		cmd->args = 0;
		cmd->redirs = 0;
	}
	return (cmd);
}

void	parsed_cmd_cleanup(t_parsed_cmd **cmd)
{
	ft_lstclear(&(*cmd)->args, do_nothing);
	ft_lstclear(&(*cmd)->redirs, free);
	free(*cmd);
	*cmd = NULL;
}

void	print_parsed_cmd(t_parsed_cmd *cmd)
{
	ft_printf("PARSED_CMD\n");
	if (!cmd)
	{
		ft_printf("(NULL)\n");
	}
	else
	{
		ft_printf("~~args~~\n");
		print_args_list(cmd->args);
		ft_printf("~~redirs~~\n");
		print_redirs(cmd->redirs);
	}
	return ;
}

void	print_parsed_cmd2(t_parsed_cmd *cmd)
{
	if (!cmd)
	{
		ft_printf("(NULL)\n");
	}
	else
	{
		print_args_list2(cmd->args);
		print_redirs2(cmd->redirs);
	}
	ft_printf("\n");
	return ;
}

static void	print_redirs(t_list *redirs)
{
	while (redirs)
	{
		print_item(redirs->content);
		redirs = redirs->next;
	}
}

static void	print_redirs2(t_list *redirs)
{
	t_item	*item;
	ft_printf("[");
	while (redirs)
	{
		item = redirs->content;
		ft_printf("%s %s", ret_token_literal(item->modifier), item->word);
		redirs = redirs->next;
		if (redirs)
			ft_printf(" ");
	}
	ft_printf("]");
}

static void	print_args_list(t_list *args)
{
	int	count;

	count = 0;
	while (args)
	{
		ft_printf("%2d. %s\n", count, args->content);
		args = args->next;
		count++;
	}
}

static void	print_args_list2(t_list *args)
{
	ft_printf("[");
	while (args)
	{
		ft_printf("%s", args->content);
		args = args->next;
		if (args)
			ft_printf(" ");
	}
	ft_printf("]");
}
