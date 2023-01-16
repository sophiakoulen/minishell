/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoulen <skoulen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:29:17 by znichola          #+#    #+#             */
/*   Updated: 2023/01/16 16:10:00 by skoulen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **args);

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
		ret->in = NULL;
		ret->out = NULL;
	}
	else
	{
		ret->args = blueprint->args;
		ret->in = blueprint->in;
		ret->out = blueprint->out;
	}
	return (ret);
}

void	print_cmd(t_cmd *cmd)
{
	ft_printf("cmd ..................\n");
	if (!cmd)
	{
		ft_printf("\t(NULL)\n");
	}
	else
	{
		ft_printf("\t in: ");
		print_redir(cmd->in);
		ft_printf("\n\tout: ");
		print_redir(cmd->out);
		ft_printf("\n");
		print_args(cmd->args);
	}
}

static void	print_args(char **args)
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