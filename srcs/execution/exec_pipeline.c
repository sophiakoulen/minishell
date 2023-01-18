/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: znichola <znichola@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:03:02 by skoulen           #+#    #+#             */
/*   Updated: 2023/01/18 15:54:20 by znichola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Execute pipeline and return exit status of last command.

	Needs the environment to work with and send to child processes.

	If there is only one command, we don't fork.
*/
int	exec_pipeline(t_pipeline *p)
{
	t_fds	*fds;
	int		ret;

	fds = prepare_fds(p->n_cmds);
	if (p->n_cmds == 1)
		ret = simple_command(p->cmds, fds);
	else
		ret = multiple_commands(p->cmds, fds, p->n_cmds);
	cleanup_fds(fds, p->n_cmds);
	//ft_printf("return value:%d\n", ret);
	return (ret);
}
